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
/*!        \file  ara/com/types.h
 *        \brief  Types used by ara::com API
 *      \details  Specific types needed by the ara::com API for proxy, skeleton and the runtime interface.
 *        \trace  SPEC-4980253
 *********************************************************************************************************************/

#ifndef LIB_SOCAL_INCLUDE_ARA_COM_TYPES_H_
#define LIB_SOCAL_INCLUDE_ARA_COM_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <memory>
#include <vector>
#include "amsr/socal/internal/handle_type.h"
#include "amsr/socal/internal/types.h"
#include "ara/com/com_error_domain.h"
#include "ara/com/instance_identifier.h"
#include "ara/com/service_identifier.h"
#include "ara/com/variant.h"

/*!
 * \trace SPEC-4980254, SPEC-4980253, SPEC-498025  
 */
namespace ara {
namespace com {

/*!
 * \brief Container for a list of service handles
 * \vpublic
 * \trace SPEC-4980260
 */
template <typename T>
using ServiceHandleContainer = std::vector<T>;

/*!
 * \brief  Function wrapper for the handler function that gets called
 * \vpublic
 * \trace SPEC-4980261
 */
template <typename T>
using FindServiceHandler = std::function<void(ServiceHandleContainer<T>)>;

/*!
 * \brief Definition of service version type
 * \vpublic
 */
using ServiceVersion = std::uint32_t;

/*!
 * \brief The policy of the event cache update.
 * \vpublic
 * \trace SPEC-4980262
 */
enum class EventCacheUpdatePolicy : uint8_t {
  /*!
   * \brief Last N Policy.
   * \details With this policy, for each call of Update the new available events are added to the cache. If they do not
   * fit into the cache, the least recently used entries are discarded first.
   */
  kLastN,
  /*!
   * \brief Newest N Policy.
   * \details With this policy, for each call of Update the cache gets cleared first and then filled with the new
   * available events. Even if no event has arrived since the last call to Update, the cache gets cleared.
   */
  kNewestN
};

/*!
 * \brief Function wrapper for the handler function that gets called when new event data arrives.
 * \vpublic
 * \trace SPEC-4980268
 */
using EventReceiveHandler = std::function<void()>;

/*!
 * \brief Holds a list of pointers to data samples and is received via event communication.
 * \vpublic
 * \trace SPEC-4980266
 */
template <typename T>
using SampleContainer = std::vector<T>;

/*!
 * \brief Pointer to a data sample allocated by the runtime.
 * \vpublic
 * \trace SPEC-4980267
 */
template <typename T>
using SampleAllocateePtr = std::unique_ptr<T>;

/*!
 * \brief The subscription state of an event.
 * \vpublic
 * \trace SPEC-4980269
 */
enum class SubscriptionState : uint8_t { kSubscribed = 0U, kNotSubscribed = 1U, kSubscriptionPending = 2U };

/*!
 * \brief Function representing a subscription state change handler.
 * \vpublic
 * \trace SPEC-4980270
 */
using SubscriptionStateChangeHandler = std::function<void(ara::com::SubscriptionState const)>;

/*!
 * \brief The processing modes for the service implementation side.
 * \vpublic
 * \trace SPEC-4980271
 */
enum class MethodCallProcessingMode : uint8_t {
  /*!
   * \brief Polling
   * \details Instead of calling a provided service method, the reactor collects incoming service method invocations.
   * The processing of each invocation is explicitly triggered by calling ProcessNextMethodCall().
   */
  kPoll,

  /*!
   * \brief Event-driven, concurrent
   * \details The reactor activates the invoked service method when the invocation arrives. Consumer concurrent calls
   * are allowed and will be processed concurrently on provider side by using different threads. This is the default
   * mode.
   */
  kEvent,

  /*!
   * \brief Event-driven, sequential
   * \details The reactor activates the invoked service method when the invocation arrives. Consumer concurrent calls
   * are allowed, but will not be processed concurrently on provider side, by instead executing them one after the other
   * to avoid the need of synchronization mechanisms in the implementation providing the service method.
   */
  kEventSingleThread
};

/*!
 * \brief Function representing a filter function provided by the programmer.
 * \tparam SampleType Type of single samples
 * \param[in] sample The sample to evaluate.
 * \return true means to accept/keep the sample in the Update() call.
 * \vpublic
 * \trace SPEC-4980376
 */
template <typename SampleType>
using FilterFunction = std::function<bool(SampleType const& sample)>;

}  // namespace com
}  // namespace ara

#endif  // LIB_SOCAL_INCLUDE_ARA_COM_TYPES_H_