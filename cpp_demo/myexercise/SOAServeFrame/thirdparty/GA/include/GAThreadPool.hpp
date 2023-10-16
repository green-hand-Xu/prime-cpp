#ifndef __GAThreadPool_HPP__
#define __GAThreadPool_HPP__

#include <functional>

#include "include/CTPL/ctpl_stl.h"

/**
 * @brief Thread pool support header.
 *
 * use metod async(...) to run your code in thread pool.
 *
 * The thread pool create only 2 thread by default,
 * resizeThreadPool(...) is used to reset the number of threads in pool.
 *
 */

namespace GA {
namespace GAThreadPool {
/**
 * @brief Global thread pool object.
 *
 */
class __GAThreadPoolInstance {
  static constexpr const int DEFAULT_THREAD_COUNT = 2;

private:
  __GAThreadPoolInstance(const __GAThreadPoolInstance &) = delete;
  __GAThreadPoolInstance(const __GAThreadPoolInstance &&) = delete;
  __GAThreadPoolInstance &operator=(const __GAThreadPoolInstance &) = delete;
  __GAThreadPoolInstance &operator=(const __GAThreadPoolInstance &&) = delete;

  __GAThreadPoolInstance() : _threads(DEFAULT_THREAD_COUNT){};
  ~__GAThreadPoolInstance(){};

  ctpl::thread_pool _threads;

public:
  /**
   * @brief Get the Pool object.
   *
   * @return ctpl::thread_pool&
   */
  static ctpl::thread_pool &getPool() {
    static __GAThreadPoolInstance pool;
    return pool._threads;
  }
};

/**
 * @brief Reset the number of threads that working in thread pool.
 *
 * @param threadCount Total size of threads.
 */
inline void resizeThreadPool(int threadCount) {
  __GAThreadPoolInstance::getPool().resize(threadCount);
}

/**
 * @brief Run func in thread pool.
 *
 * @param func
 */
inline void async(std::function<void()> func) {
  __GAThreadPoolInstance::getPool().push([func](int) { func(); });
}

}  // namespace GAThreadPool
}  // namespace GA

#endif