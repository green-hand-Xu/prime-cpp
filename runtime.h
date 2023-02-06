/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  runtime.h
 *        \brief  Contains central runtime module of the ara::com API
 *      \details  This module plays a central role for the ara::com. It manages all bindings and connects them to the
 *                corresponding proxy and skeleton classes (see broker pattern). The generated interfaces
 *                (proxy/skeleton) delegating their middleware interactions (like service discovery) to the runtime.
 *                The runtime then dispatches every request to the binding.
 *********************************************************************************************************************/

#ifndef LIB_SOCAL_INCLUDE_ARA_COM_RUNTIME_H_
#define LIB_SOCAL_INCLUDE_ARA_COM_RUNTIME_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <atomic>
#include <memory>
#include <mutex>
#include <utility>

#include "amsr/generic/singleton_wrapper.h"
#include "amsr/socal/internal/configuration/configuration.h"
#include "amsr/socal/internal/configuration/configuration_provider.h"
#include "amsr/socal/internal/instance_specifier_lookup_table.h"
#include "amsr/socal/internal/logging/ara_com_logger.h"
#include "amsr/socal/internal/thread_pool.h"
#include "amsr/socal/internal/types.h"
#include "amsr/thread/thread.h"
#include "amsr/timer/threadsafe_timer_manager.h"
#include "ara/com/instance_identifier.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/optional.h"
#include "ara/core/result.h"
#include "ara/core/string_view.h"
#include "osabstraction/io/reactor1/reactor1.h"
#include "vac/container/c_string_view.h"
#include "vac/container/static_vector.h"
#include "vac/container/string_literals.h"

namespace ara {
namespace com {

namespace trace {

/*!
 * \brief 转发IPC绑定跟踪接口的声明，以将SOCAL与IPC标头解耦
 */
class IpcBindingTraceIf;

}  // namespace trace

namespace internal {

// VECTOR NC Metric-OO.WMC.One: MD_Socal_Metric-OO.WMC.methods_per_class_is_above_limit
/*!
 * \brief Runtime类创建必要的绑定实例。
 * \vprivate Vector component internal API.
 */
class Runtime final {
 public:
  /*!
   * \brief 用于缩短线程池配置分配名称的类型别名
   */
  using AssignmentName = amsr::socal::internal::configuration::AssignmentName;

  /*!
   * \brief 内部配置类型的类型别名
   */
  using Configuration = amsr::socal::internal::configuration::Configuration;

  /*!
   * \brief 内部配置提供程序类型的类型别名
   */
  using ConfigurationProvider = amsr::socal::internal::configuration::ConfigurationProvider<>;

  /*!
   * \brief Returns an singleton wrapped instance of Runtime class.
   * \return Singleton wrapped Runtime instance.
   * \pre -
   * \context ANY
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  static amsr::generic::Singleton<Runtime>& getSingletonInstance() noexcept;

  /*!
   * \brief Destructor invokes the shutdown sequence if not already de-initialized.
   * \pre -
   * \context App
   * \reentrant FALSE
   * \synchronous TRUE
   */
  ~Runtime() noexcept;

  /*!
   * \brief Runtime shall be non-copyable.
   */
  Runtime(Runtime const&) = delete;

  /*!
   * \brief Delete assignment operator
   */
  void operator=(Runtime const&) = delete;

  /*!
   * \brief Initializes internal runtime components.
   * \param[in] config "ara::com" specific configuration and binding-related parameters.
   * \return "ara::core::Result" with "ara::com::ComErrc::runtime_not_running"
   *         as error if "runtime" is not running else "ara::core::Result" with
   *         no value and no error.
   * \pre "ara::com::internal::Runtime" must not be already initialized.
   * \pre Static memory must have been allocated.
   * \pre All instance specifiers from the configuration must be known.
   * \pre When using SomeIpBinding, SomeIpDaemon must be running and must accept connection requests
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  ara::core::Result<void> InitializeCommunication(Configuration const& config = Configuration{}) noexcept;

  /*!
   * \brief Shuts down the runtime.
   * \return "ara::core::Result" with no value and no error.
   * \pre "ara::com::internal::Runtime" must be initialized.
   * \pre "StopFindService()" must have been called for all active "StartFindService()" requests.
   * \pre Proxies and skeletons must have been stopped.
   * \context Shutdown
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  ara::core::Result<void> DeInitializeCommunication() noexcept;

  /*!
   * \brief       Trigger handling of pending reactor events (received or transmitted packets, expired timers).
   * \return      True if any packet (timer handling or any rx/tx task) has been processed, false otherwise.
   * \pre         "ara::com::internal::Runtime" must be initialized.
   *              Runtime processing mode must be configured to 'kPolling'.
   * \context     App | Init
   * \threadsafe  FALSE
   * \reentrant   FALSE
   * \synchronous TRUE
   */
  bool ProcessPolling() noexcept;

  /*!
   * \brief A skeleton calls this "Runtime" method on construction to get the thread-pool assigned to the concrete
   *        service instance. If there's no reference to a user-specific thread-pool for this object, the default
   *        thread-pool is returned as a reference.
   * \param[in] assignment_identifier The assignment name string to identify the threadpool.
   *                              If no specific assignment identifier is passed, the default
   *                              thread pool is assigned (kAssignmentNameDefaultThreadPool).
   * \return The thread-pool assigned to this service interface instance.
   *         In case of no user-specific assignment, the default thread-pool is returned as a reference.
   * \pre ara::com::internal::Runtime must be initialized.
   * \context ANY
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::ThreadPool& RequestThreadPoolAssignment(
      amsr::socal::internal::ThreadPoolAssignmentIdentifier const& assignment_identifier =
          amsr::socal::internal::kAssignmentNameDefaultThreadPool) noexcept;

  /*!
   * \brief Returns a reference to the underlying instance specifier lookup table.
   * \returns The instance of the "InstanceSpecifierLookupTable".
   * \pre "ara::com::internal::Runtime" must be initialized.
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::InstanceSpecifierLookupTable& GetInstanceSpecifierLookupTable() noexcept;

  /*!
   * \brief Returns a reference to the underlying P-Port instance specifier lookup table.
   * \returns The instance of the "InstanceSpecifierLookupTable".
   * \pre "ara::com::internal::Runtime" must be initialized.
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::InstanceSpecifierLookupTable const& GetProvidedInstanceSpecifierLookupTable() const noexcept;

  /*!
   * \brief Returns a reference to the underlying R-Port instance specifier lookup table.
   * \returns The instance of the "InstanceSpecifierLookupTable".
   * \pre "ara::com::internal::Runtime" must be initialized.
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::InstanceSpecifierLookupTable const& GetRequiredInstanceSpecifierLookupTable() const noexcept;

  /*!
   * \brief Gets the configured runtime processing mode.
   * \return The configured runtime processing mode.
   * \pre -
   * \context ANY
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::configuration::RuntimeProcessingMode GetProcessingMode() const noexcept;

  /*!
   * \brief Returns reference to internal mutex to allow a worker threads
   *        to synchronize with the user threads in Polling processing mode.
   * \return reference to the mutex used internally to guarantee ProcessPolling thread safety
   * \pre -
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  std::recursive_mutex& GetPollingModeLock() noexcept;

  /*!
   * \brief Returns reference to the abstract ara::com configuration model.
   * \return reference to the ara::com configuration model
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::socal::internal::configuration::Configuration const& GetConfig() const noexcept;

  /*!
   * \brief  Returns the used configuration approach.
   * \details The selected configuration is determined based on the file system availability of the JSON config files.
   * \return Used configuration approach.
   * \pre    -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   * \vprivate Vector component internal API
   */
  amsr::socal::internal::configuration::ConfigApproach GetConfigApproach() const noexcept;

  /*!
   * \brief  Sets the desired configuration approach.
   * \param[in] config_approach The configuration approach to use in the initialization.
   * \pre    -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   * \vprivate Vector component internal API
   */
  void SetConfigApproach(amsr::socal::internal::configuration::ConfigApproach const config_approach) noexcept;

  /*!
   * \brief Returns reference to the os abstraction Reactor1 object.
   * \return reference to the reactor object
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  osabstraction::io::reactor1::Reactor1& GetReactor() noexcept;

  /*!
   * \brief Returns reference to the vac library ThreadSafeTimerManager object.
   * \return reference to the timer manager
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  amsr::timer::ThreadSafeTimerManager& GetTimerManager() noexcept;

  /*!
   * \brief Add a new mapping entry between a InstanceSpecifier and a InstanceIdentifier.
   * \details This API must be called multiple times to register all known mappings.
   * Example to initialize mapping of one InstanceSpecifier to two InstanceIdentifiers.
   * MapInstanceSpecifierToInstanceId("Ipc", InstanceSpecifier("exec/rootSwc/rport0"), InstanceIdentifier("Ipc:5"));
   * MapInstanceSpecifierToInstanceId("Ipc", InstanceSpecifier("exec/rootSwc/rport0"), InstanceIdentifier("Ipc:78"));
   *
   * Hint: The lookup table does not prevent the duplicate mapping of one InstanceSpecifier to multiple identical
   * InstanceIdentifiers. The user of this class must ensure that every InstanceSpecifier to InstanceIdentifier mapping
   * is registered only one time.
   * Will be called during initialization time of the bindings.
   * \param[in] binding_name Name of the corresponding binding.
   * \param[in] instance_specifier The instance specifier which will be the key for the new entry.
   * \param[in] instance_identifier The instance identifier which will be the value for the new entry.
   *                                Expected format: "<binding_name>:<binding specific instance ID>".
   * \param[in] service_shortname_path The short-name path of this service interface.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void MapInstanceSpecifierToInstanceId(
      ::vac::container::CStringView const& binding_name, ara::core::InstanceSpecifier const& instance_specifier,
      ara::com::InstanceIdentifier const& instance_identifier,
      amsr::socal::internal::ServiceShortNamePath const& service_shortname_path) noexcept;

  /*!
   * \brief Map an InstanceIdentifier to the corresponding P-Port InstanceSpecifier.
   * \param[in] binding_name Name of the corresponding binding.
   * \param[in] instance_specifier The instance specifier which will be the key for the new entry.
   * \param[in] instance_identifier The instance identifier which will be the value for the new entry.
   *                                Expected format: "<binding_name>:<binding specific instance ID>".
   * \param[in] service_shortname_path The short-name path of this service interface.
   * \pre       The same InstanceIdentifier and InstanceSpecifier combination must have not been mapped earlier.
   * \context     BindingInit
   * \threadsafe  FALSE
   * \reentrant   FALSE
   * \synchronous TRUE
   */
  void MapProvidedInstanceSpecifierToInstanceId(
      ::vac::container::CStringView const& binding_name, ara::core::InstanceSpecifier const& instance_specifier,
      ara::com::InstanceIdentifier const& instance_identifier,
      amsr::socal::internal::ServiceShortNamePath const& service_shortname_path) noexcept;

  /*!
   * \brief Map an InstanceIdentifier to the corresponding R-Port InstanceSpecifier.
   * \param[in] binding_name Name of the corresponding binding.
   * \param[in] instance_specifier The instance specifier which will be the key for the new entry.
   * \param[in] instance_identifier The instance identifier which will be the value for the new entry.
   *                                Expected format: "<binding_name>:<binding specific instance ID>".
   * \param[in] service_shortname_path The short-name path of this service interface.
   * \pre       The same InstanceIdentifier and InstanceSpecifier combination must have not been mapped earlier.
   * \context     BindingInit
   * \threadsafe  FALSE
   * \reentrant   FALSE
   * \synchronous TRUE
   */
  void MapRequiredInstanceSpecifierToInstanceId(
      ::vac::container::CStringView const& binding_name, ara::core::InstanceSpecifier const& instance_specifier,
      ara::com::InstanceIdentifier const& instance_identifier,
      amsr::socal::internal::ServiceShortNamePath const& service_shortname_path) noexcept;

  /*!
   * \brief Replace one of the instance identifiers to which an instance specifier is mapped.
   * \details Use of this API is discouraged and not required at all if correct mappings between instance specifiers to
   *          instance ids are defined in your application model.
   * \param[in] instance_specifier The instance specifier.
   * \param[in] old_identifier The instance identifier to be replaced.
   * \param[in] new_identifier The instance identifier to replace the instance identifier to be replaced.
   * \return If the instance identifier was found and updated, true is returned. Otherwise, false is returned.
   * \pre Runtime::Initialize() must have been called.
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  bool RemapInstanceSpecifierToInstanceId(ara::core::InstanceSpecifier const& instance_specifier,
                                          InstanceIdentifier const& old_identifier,
                                          InstanceIdentifier const& new_identifier) noexcept;

  /*!
   * \brief Removes the given InstanceIdentifier from the provided instance specifier table.
   * \param[in] instance_specifier The instance specifier which will be the key for the entry to be removed.
   * \param[in] instance_identifier The instance identifier which will be the value for the entry to be removed.
   * \pre -
   * \context     BindingShutdown
   * \threadsafe  FALSE
   * \reentrant   FALSE
   * \synchronous TRUE
   */
  void RemoveProvidedInstanceSpecifierEntry(ara::core::InstanceSpecifier const& instance_specifier,
                                            ara::com::InstanceIdentifier const& instance_identifier) const noexcept;

  /*!
   * \brief Removes the given InstanceIdentifier from the required instance specifier table.
   * \param[in] instance_specifier The instance specifier which will be the key for the entry to be removed.
   * \param[in] instance_identifier The instance identifier which will be the value for the entry to be removed.
   * \pre -
   * \context     BindingShutdown
   * \threadsafe  FALSE
   * \reentrant   FALSE
   * \synchronous TRUE
   */
  void RemoveRequiredInstanceSpecifierEntry(ara::core::InstanceSpecifier const& instance_specifier,
                                            ara::com::InstanceIdentifier const& instance_identifier) const noexcept;

  /*!
   * \brief Default initializes the Runtime.
   * \pre -
   * \context Init
   * \reentrant FALSE
   * \synchronous TRUE
   */
  Runtime() = default;

 private:
  /*!
   * \brief ServiceInstanceAssignment container.
   */
  using ServiceInstanceAssignmentContainer = vac::container::StaticVector<AssignmentName>;

  /*!
   * \brief Each thread-pool contained in the Runtime is assigned to a number of service instances identified by the
   * service interface name and the ara::com::InstanceIdentifier.
   * The thread-pools act as a key. Each thread-pool as a key has multiple service instances assigned as the value
   * (static vector). Each element of this vector represents one service instance that refers to the thread-pool to use.
   */
  using ThreadPoolMapElement = std::pair<amsr::socal::internal::ThreadPool, ServiceInstanceAssignmentContainer>;

  /*!
   * \brief  Internal shared initialization.
   * \return Positive result or error.
   * \error  amsr::someip_binding::internal::SomeIpBindingErrc::json_loading_failure
   *           if component specific JSON configuration could not be found or loaded.
   * \error  amsr::someip_binding::internal::SomeIpBindingErrc::json_parsing_failure
   *           if component specific JSON configuration parsing failed.
   * \error  amsr::ipc_binding_core::internal::IpcBindingErrc::json_loading_failure
   *           if component specific JSON configuration could not be found or loaded.
   * \error  amsr::ipc_binding_core::internal::IpcBindingErrc::json_parsing_failure
   *           if component specific JSON configuration parsing failed.
   * \pre Runtime must not be already initialized
   * \pre SomeIpDaemon be running and must accept connection requests
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  ara::core::Result<void> InitializeInternal() noexcept;

  /*!
   * \brief Initializes the thread-pools.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void InitializeThreadPools() noexcept;

  /*!
   * \brief De-initializes the thread-pools.
   * \pre -
   * \context Shutdown
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void DeinitializeThreadPools() noexcept;

  /*!
   * \brief Initializes the reactor thread.
   * \param[in] thread_config The reactor thread configuration.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void InitializeReactorThread(amsr::thread::ThreadConfig const& thread_config) noexcept;

  /*!
   * \brief De-initializes the reactor thread.
   * \pre -
   * \context Shutdown
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void DeinitializeReactorThread() noexcept;

  /*!
   * \brief Generated method to initialize all present bindings.
   * \return Positive result or error.
   * \error  amsr::someip_binding::internal::SomeIpBindingErrc::json_loading_failure
   *                if component specific JSON configuration could not be found or loaded.
   * \error  amsr::someip_binding::internal::SomeIpBindingErrc::json_parsing_failure
   *                if component specific JSON configuration parsing failed.
   * \error  amsr::ipc_binding_core::internal::IpcBindingErrc::json_loading_failure
   *                if component specific JSON configuration could not be found or loaded.
   * \error  amsr::ipc_binding_core::internal::IpcBindingErrc::json_parsing_failure
   *                if component specific JSON configuration parsing failed.
   * \pre SomeIpDaemon be running and must accept connection requests
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  ara::core::Result<void> InitializeBindings() noexcept;

  /*!
   * \brief Generated method to initialize all static memory.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void InitializeLifecycleManager() noexcept;

  /*!
   * \brief Generated method to deinitialize all static memory.
   * \pre -
   * \context Shutdown
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void DeinitializeLifecycleManager() noexcept;

  /*!
   * \brief Generated method to start dynamic actions / events of all present bindings.
   * \details In this API context all events triggered by the reactor thread must be activated / registered:
   *          - Register received events
   *          - Start any message transmission
   *          - Start timers
   * \pre InitializeBindings() has been called.
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void StartBindings() noexcept;

  /*!
   * \brief      Trigger handling of pending reactor events (received or transmitted packets, expired timers) in polling
   *             mode.
   * \return     True if any packet (timer handling or any rx/tx task) has been processed, false otherwise.
   * \pre        Runtime processing mode must be configured to 'kPolling'.
   * \context    App | Init
   * \threadsafe TRUE
   * \reentrant  FALSE
   * \synchronous TRUE
   */
  bool ProcessPollingInternal() noexcept;

  /*!
   * \brief Generated method to destroy all present BindingInterfaces present in this application.
   * \details Important: The bindings must be destroyed here before the reactor_ attribute gets destroyed.
   *          Otherwise possible calls in binding destructors to the reactor (e.g. UnregisterEventHandler()) will fail.
   * \pre reactor thread must be stopped.
   *      This is necessary to fulfill preconditions of the binding deinitialization functions.
   * \context Shutdown
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void DeinitializeBindings() noexcept;

  /*!
   * \brief Handle error: API called but runtime is not initialized or running.
   * \details Log a fatal error and calls ara::core::Abort.
   * \pre -
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void HandleErrorNotRunning() const noexcept;

  /*!
   * \brief Handle error: API called but runtime is already initialized and running.
   * \details Log a fatal error and calls ara::core::Abort.
   * \pre -
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void HandleErrorAlreadyRunning() const noexcept;

  /*!
   * \brief Get default thread pool configured object.
   * \return Default thread pool configuration.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  static amsr::socal::internal::configuration::ThreadPoolConfig GetDefaultThreadPoolConfig() noexcept;

  /*!
   * \brief Get proxy method thread pool configured object.
   * \return Proxy method thread pool configuration.
   * \pre -
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  static amsr::socal::internal::configuration::ThreadPoolConfig GetProxyMethodThreadPoolConfig() noexcept;

  /*!
   * \brief Get reactor thread configured object.
   * \return Reactor thread configuration.
   * \pre -
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  static constexpr amsr::thread::ThreadConfig GetReactorThreadConfig() noexcept;
  /*!
   * \brief Validate the InstanceSpecifiers configured in thread pool AssignmentConfig.
   * \throws InstanceSpecifierException, in case AssignmentName of the thread pool isn't a valid meta-model
   *         identifier/short name path.
   * \pre All instance specifiers from the configuration must be known
   * \context App
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void ValidateThreadpoolAssignmentConfig() const noexcept;

  /*!
   * \brief Create reactor and timer manager.
   * \details ara::core::Abort is called if reactor construction fails.
   * \param[in] num_of_callbacks max number of callbacks the reactor needs to handle.
   * \context Init
   * \threadsafe FALSE
   * \reentrant FALSE
   * \synchronous TRUE
   */
  void InitializeReactorAndTimerManager(std::uint16_t num_of_callbacks) noexcept;

  /*!
   * \brief An instance of a logger.
   */
  amsr::socal::internal::logging::AraComLogger logger_{amsr::socal::internal::logging::kAraComLoggerContextId,
                                                       amsr::socal::internal::logging::kAraComLoggerContextDescription,
                                                       "Runtime"};

  /*!
   * \brief Lookup table storing mappings between InstanceSpecifiers and InstanceIdentifiers.
   */
  amsr::socal::internal::InstanceSpecifierLookupTable instance_specifier_table_{logger_};

  /*!
   * \brief Selected configuration approach for the whole ara::com stack.
   */
  amsr::socal::internal::configuration::ConfigApproach config_approach_{
      amsr::socal::internal::configuration::ConfigApproach::kClassic};

  /*!
   * \brief Abstract ara::com configuration model
   */
  amsr::socal::internal::configuration::Configuration config_{};

  /*!
   * \brief reactor_done_ globally declare if reactor created or not
   */
  std::atomic<bool> reactor_done_{false};

  /*!
   * \brief reactor_ object
   */
  ara::core::Optional<osabstraction::io::reactor1::Reactor1> reactor_{};

  /*!
   * \brief timer_manager_ object
   */
  ara::core::Optional<amsr::timer::ThreadSafeTimerManager> timer_manager_{};

  /*!
   * \brief reactor_thread_ reactor thread
   */
  amsr::thread::Thread reactor_thread_{};

  /*!
   * \brief Signalizes if the Runtime instance is still alive for multi-threaded applications.
   * \details Currently the Runtime object construction and Initialization is done at two different steps.
   *          This flag is used to make sure the Runtime is not only constructed but also initialized.
   */
  std::atomic<bool> is_running_{false};

  /*!
   * \brief One default thread-pool if there are no user-defined thread-pools configured.
   *
   * \details The Thread pool is created when runtime is initialized, and destroyed upon calling Shutdown.
   */
  ara::core::Optional<amsr::socal::internal::ThreadPool> default_thread_pool_{};

  /*!
   * \brief Type-alias for the thread-pool container. The static vector is filled during initialization time once.
   * All user-specific thread-pools will be emplaced and the service interface instances using these thread-pools
   * will be assigned to the individual elements.
   */
  using ThreadPoolContainer = vac::container::StaticVector<ThreadPoolMapElement>;

  /*!
   * \brief All thread-pools are hold in the Runtime object.
   */
  ThreadPoolContainer thread_pools_{};

  /*!
   * \brief Lock to synchronize execution of ProcessPolling.
   * \details Due to threading design the reactor must never be triggered concurrently.
   *          The lock is recursive because ProcessPolling is called internal during bindings initialization.
   */
  std::recursive_mutex process_polling_lock_{};

  FRIEND_TEST(UT__AraCom__Runtime, InitializeCommunication);
  FRIEND_TEST(UT__AraCom__Runtime, InitializeCommunication__Reinitialization);
  FRIEND_TEST(UT__AraCom__Runtime, InitializeCommunicationWithWrongInstanceSpecifier);
  FRIEND_TEST(UT__AraCom__Runtime, RequestThreadPoolAssignment__NotRunning);
};

}  // namespace internal

namespace runtime {

/*!
 * \brief       Trigger handling of pending reactor events (received or transmitted packets, expired timers).
 * \return      True if any packet (timer handling or any rx/tx task) has been processed, false otherwise.
 * \pre         The adaptive stack must have been initialized using ara::core::Initialize().
 *              Runtime processing mode must be configured to 'kPolling'.
 * \context     App | Init
 * \threadsafe  FALSE
 * \reentrant   FALSE
 * \vpublic
 * \synchronous TRUE
 */
bool ProcessPolling() noexcept;

/*!
 * \brief Replace one of the instance identifiers to which an instance specifier is mapped.
 * \details Use of this API is discouraged and not required at all if correct mappings between instance specifiers to
 *          instance ids are defined in your application model.
 * \param[in] instance_specifier The instance specifier.
 * \param[in] old_identifier The instance identifier to be replaced.
 * \param[in] new_identifier The instance identifier to replace the instance identifier to be replaced.
 * \return If the instance identifier was found and updated, true is returned. Otherwise, false is returned.
 * \pre The adaptive stack must have been initialized using ara::core::Initialize().
 * \context App
 * \threadsafe FALSE
 * \reentrant FALSE
 * \vpublic
 * \synchronous TRUE
 */
[
    [deprecated("runtime::RemapInstanceSpecifierToInstanceId() will be removed. InstanceSpecifiers will be loaded "
                "during runtime from the component specific configuration files; AMSR-26411.")]] bool
RemapInstanceSpecifierToInstanceId(::ara::core::InstanceSpecifier const& instance_specifier,
                                   ::ara::com::InstanceIdentifier const& old_identifier,
                                   ::ara::com::InstanceIdentifier const& new_identifier) noexcept;

/*!
 * \brief Returns all instance identifiers which match the provided instance specifier.
 * \param[in] instance The provided instance specifier which is used to look up the corresponding service instance
 * identifiers.
 * \return A container of matching instance identifiers, which could also be empty.
 * \pre -
 * \context App
 * \threadsafe FALSE
 * \vpublic
 * \synchronous TRUE
 * \reentrant FALSE
 * \trace SPEC-8053578
 */
InstanceIdentifierContainer ResolveInstanceIDs(ara::core::InstanceSpecifier instance) noexcept;

}  // namespace runtime

}  // namespace com
}  // namespace ara

#endif  // LIB_SOCAL_INCLUDE_ARA_COM_RUNTIME_H_

/*!
 * \exclusivearea ::ara::com::internal::Runtime::process_polling_lock_
 * Used to synchronize execution of ProcessPolling.
 *
 * \protects ::ara::com::internal::Runtime::ProcessPolling is the protected resource of a WorkerThread object.
 * \usedin ::ara::com::internal::Runtime::ProcessPollingInternal
 * \exclude All other methods of the ::ara::com::internal::Runtime  object.
 * \length MEDIUM synchronizes execution of the reactor.
 * \endexclusivearea
 */