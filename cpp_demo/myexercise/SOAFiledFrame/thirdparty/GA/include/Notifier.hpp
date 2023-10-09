#ifndef __Notifier_HPP__
#define __Notifier_HPP__

#include <bits/stl_algo.h>
#include <cstdint>
#include <functional>
#include <list>
#include "GA/include/Core.hpp"
#include "GA/include/GAThreadPool.hpp"

/**
 * @brief 这里定义了一个用于调用回调的基础代码类。
 * 它可以把所有回调放到待触发列表中，然后通过一个invoke函数来进行触发。
 * 
 * 为了做异步调用，我们在这里使用了GAThreadPool，这是我们自己的一个线程池组件，当然它也是基于一个开源的CPTL组件。
 * 后续我们可能使用其他的组件来构建线程池，到时这个类不需要进行任何变更。
 * 
 * +=的关联方法来自于C#的事件写法，我觉得这种方式比较直白，能让人一眼看上去就明白是把一个回调追加到它后面。
 * 当然如果你细化古老的方式，我们也提供了prepend用于在头部追加，和append用于在尾部追加。
 * 
 * 在watch中，我们觉得validator可以在当前线程完成，而没必要提供过度冗余的线程池开销，所以我们保留了这个特性。
 */

using namespace GA::GAThreadPool;

/// @brief Common notifier, call given handler when condition meets.
/// @tparam Arg type, can be any type, no data type dependance. 
template <typename T>
class Notifier {
public:
  // Handler to handle value changing and notifying.
  using ValueHandler = std::function<void(T arg)>;
  using ValueValidator = std::function<bool(const T& arg)>;
  // Collection of value handler.
  using ValueHandlers = std::list<ValueHandler>;

  Notifier() {}
  virtual ~Notifier() { 
    clear();
    clearWatch(); 
  }

  /// @brief Invoke the notifier.
  /// @param oldValue An old value, which means previous value, should always be the value notified last time.
  /// @param newValue Latest value, which also means current value.
  /// @return Total count of invoked handlers.
  /// @exception No exception is handled.
  int invoke(const T& arg) noexcept {
    auto count = invokeHandlers(arg, _handlers, true);
    static_cast<void>(invokeHandlers(arg, _watchingHandlers, false));

    return count;
  }

  /**
   * @brief Section of thread pool.
   */
public:
  /**
   * @brief Set true to run invoked and watching methods in thread pool.
   * 
   * @note Use GAThreadPool to run async methods, so you can change threads setting via GAThreadPool.
   */
  GAProperty<bool> isAsync{true};

public:
 /// @brief Watch received value from @ref invoke(), call handler when validator
 /// returns true.
 /// @param validator Return true when handler should be executed.
 /// @param handler Value handler.
  void watch(ValueValidator validator, ValueHandler handler) noexcept {
    _watchingHandlers.push_back(
        [this, validator ,handler](auto arg) {
          if (validator(arg)) {
            invokeHandler(handler, arg);
          }
        });
  }

  /// @brief Clear all handlers setup via watch(...).
  void clearWatch() { 
    _watchingHandlers.clear(); 
  }

protected:
  ValueHandlers _watchingHandlers;

public:
  /// @brief Append handle to list.
  /// @param handler 
  void operator+=(const ValueHandler& handler) { 
    append(handler);
  }

  /// @brief Remove value handler from list.
  /// @param handler 
  /// @note Does not work well now.
  void operator-=(const ValueHandler& handler) {
    //cannot do it now,
     (void)(handler);
  }

  /// @brief Append value changed handler, handler will invoke whenever value changed via invoke(...).
  /// @param handler 
  /// @note All handler is queued, so don't try to update/replace an existing handler by this method, 
  /// the only way to replace is clear() and call onChange() again.
  void append(const ValueHandler& handler) { 
    _handlers.emplace_back(handler); 
  }

  /// @brief Add value changed handler to front of handlers, handler will invoke whenever value changed via invoke(...).
  /// @param handler 
  /// @note All handler is queued, so don't try to update/replace an existing handler by this method, 
  /// the only way to replace is clear() and call onChange() again.
  void prepend(const ValueHandler& handler) { 
    _handlers.emplace_front(handler); 
  }

  /// @brief Clear all onchanged handlers.
  void clear() noexcept { 
    _handlers.clear(); 
  }

protected:
  ValueHandlers _handlers;

private:
  /// @brief Internal helper method to invoke every handler in handlers.
  /// @param arg 
  /// @param methods 
  /// @param useIsAsync Set true to use property 'isAsync', false to invoke directly.
  /// @return 
  int invokeHandlers(const T& arg, ValueHandlers methods, bool useIsAsync) noexcept{
    int count{0};
    for (auto handler : methods) {
      if (!handler) {
        continue;
      }
      if (useIsAsync) {
        invokeHandler(handler, arg);
      } else {
        handler(arg);
      }
      count++;
    }

    return count;
  }

  inline void invokeHandler(ValueHandler handler, const T& arg) {
    if (isAsync) {
      async([handler, arg]() { handler(arg); });
    } else {
      handler(arg);
    }
  }
};

#endif