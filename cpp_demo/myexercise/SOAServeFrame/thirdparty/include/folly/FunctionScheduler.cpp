/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FunctionScheduler.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

using std::chrono::microseconds;
using std::chrono::steady_clock;

namespace folly {

namespace {

struct ConsistentDelayFunctor {
  const microseconds constInterval;

  explicit ConsistentDelayFunctor(microseconds interval)
      : constInterval(interval) {
    if (interval < microseconds::zero()) {
      throw std::invalid_argument(
          "FunctionScheduler: "
          "time interval must be non-negative");
    }
  }

  steady_clock::time_point operator()(steady_clock::time_point curNextRunTime,
                                      steady_clock::time_point curTime) const {
    auto intervalsPassed = (curTime - curNextRunTime) / constInterval;
    return (intervalsPassed + 1) * constInterval + curNextRunTime;
  }
};

struct ConstIntervalFunctor {
  const microseconds constInterval;

  explicit ConstIntervalFunctor(microseconds interval)
      : constInterval(interval) {
    if (interval < microseconds::zero()) {
      throw std::invalid_argument(
          "FunctionScheduler: "
          "time interval must be non-negative");
    }
  }

  microseconds operator()() const { return constInterval; }
};

struct PoissonDistributionFunctor {
  std::default_random_engine generator;
  std::poisson_distribution<microseconds::rep> poissonRandom;

  explicit PoissonDistributionFunctor(microseconds meanPoissonUsec)
      : poissonRandom(meanPoissonUsec.count()) {
    if (meanPoissonUsec.count() < 0) {
      throw std::invalid_argument(
          "FunctionScheduler: "
          "Poisson mean interval must be non-negative");
    }
  }

  microseconds operator()() { return microseconds(poissonRandom(generator)); }
};

}  // namespace

FunctionScheduler::FunctionScheduler(){}

FunctionScheduler::~FunctionScheduler() {
  // make sure to stop the thread (if running)
  bool ret = shutdown();
  if (!ret) {
  }
}

void FunctionScheduler::addFunction(std::function<void()>&& cb,
                                    microseconds interval, std::string nameID,
                                    microseconds startDelay) {
  addFunctionInternal(std::move(cb), ConstIntervalFunctor(interval), nameID,
                      std::to_string(interval.count()) + "us", startDelay,
                      false /*runOnce*/);
}

void FunctionScheduler::addFunction(std::function<void()>&& cb,
                                    microseconds interval,
                                    const LatencyDistribution& latencyDistr,
                                    std::string nameID,
                                    microseconds startDelay) {
  if (latencyDistr.isPoisson) {
    addFunctionInternal(
        std::move(cb), PoissonDistributionFunctor(latencyDistr.poissonMean),
        nameID,
        std::to_string(latencyDistr.poissonMean.count()) + "us (Poisson mean)",
        startDelay, false /*runOnce*/);
  } else {
    addFunction(std::move(cb), interval, nameID, startDelay);
  }
}

void FunctionScheduler::addFunctionOnce(std::function<void()>&& cb,
                                        std::string nameID,
                                        microseconds startDelay) {
  addFunctionInternal(std::move(cb), ConstIntervalFunctor(microseconds::zero()),
                      nameID, "once", startDelay, true /*runOnce*/);
}

void FunctionScheduler::addFunctionConsistentDelay(std::function<void()>&& cb,
                                                   microseconds interval,
                                                   std::string nameID,
                                                   microseconds startDelay) {
  addFunctionInternal(std::move(cb), ConsistentDelayFunctor(interval), nameID,
                      std::to_string(interval.count()) + "us", startDelay,
                      false /*runOnce*/);
}

void FunctionScheduler::addFunctionGenericDistribution(
    std::function<void()>&& cb, IntervalDistributionFunc&& intervalFunc,
    const std::string& nameID, const std::string& intervalDescr,
    microseconds startDelay) {
  addFunctionInternal(std::move(cb), std::move(intervalFunc), nameID,
                      intervalDescr, startDelay, false /*runOnce*/);
}

void FunctionScheduler::addFunctionGenericNextRunTimeFunctor(
    std::function<void()>&& cb, NextRunTimeFunc&& fn, const std::string& nameID,
    const std::string& intervalDescr, microseconds startDelay) {
  addFunctionInternal(std::move(cb), std::move(fn), nameID, intervalDescr,
                      startDelay, false /*runOnce*/);
}

template <typename RepeatFuncNextRunTimeFunc>
void FunctionScheduler::addFunctionToHeapChecked(
    std::function<void()>&& cb, RepeatFuncNextRunTimeFunc&& fn,
    const std::string& nameID, const std::string& intervalDescr,
    microseconds startDelay, bool runOnce) {
  if (cb == nullptr) {
    throw std::invalid_argument(
        "FunctionScheduler: Scheduled function must be set");
  }
  if (fn == nullptr) {
    throw std::invalid_argument(
        "FunctionScheduler: "
        "interval distribution or next run time function must be set");
  }
  if (startDelay < microseconds::zero()) {
    throw std::invalid_argument(
        "FunctionScheduler: start delay must be non-negative");
  }

  std::unique_lock<std::mutex> l(mutex_);
  auto it = functionsMap_.find(nameID);
  // check if the nameID is unique
  if (it != functionsMap_.end() && it->second->isValid()) {
    std::string errmsg = "FunctionScheduler: a function named \"" + nameID +
                         "\" already exists"; /*  */
    throw std::invalid_argument(errmsg);
  }

  if (currentFunction_ != nullptr && currentFunction_->name == nameID) {
    std::string errmsg =
        "FunctionScheduler: a function named \"" + nameID + "\" already exists";
    throw std::invalid_argument(errmsg);
  }

  addFunctionToHeap(
      l, std::make_unique<RepeatFunc>(
             std::move(cb), std::forward<RepeatFuncNextRunTimeFunc>(fn), nameID,
             intervalDescr, startDelay, runOnce));
}

void FunctionScheduler::addFunctionInternal(
    std::function<void()>&& cb, NextRunTimeFunc&& fn, const std::string& nameID,
    const std::string& intervalDescr, microseconds startDelay, bool runOnce) {
  return addFunctionToHeapChecked(std::move(cb), std::move(fn), nameID,
                                  intervalDescr, startDelay, runOnce);
}

void FunctionScheduler::addFunctionInternal(std::function<void()>&& cb,
                                            IntervalDistributionFunc&& fn,
                                            const std::string& nameID,
                                            const std::string& intervalDescr,
                                            microseconds startDelay,
                                            bool runOnce) {
  return addFunctionToHeapChecked(std::move(cb), std::move(fn), nameID,
                                  intervalDescr, startDelay, runOnce);
}

bool FunctionScheduler::cancelFunctionWithLock(
    const std::unique_lock<std::mutex>& lock, std::string nameID) {
  assert(lock.owns_lock() == true);
  if (currentFunction_ != nullptr && currentFunction_->name == nameID) {
    static_cast<void>(functionsMap_.erase(currentFunction_->name));
    // This function is currently being run. Clear currentFunction_
    // The running thread will see this and won't reschedule the function.
    currentFunction_ = nullptr;
    cancellingCurrentFunction_ = true;
    return true;
  }
  return false;
}

bool FunctionScheduler::cancelFunction(std::string nameID) {
  std::unique_lock<std::mutex> l(mutex_);
  if (cancelFunctionWithLock(l, nameID)) {
    return true;
  }
  auto it = functionsMap_.find(nameID);
  if (it != functionsMap_.end() && it->second->isValid()) {
    cancelFunction(l, it->second);
    return true;
  }

  return false;
}

bool FunctionScheduler::cancelFunctionAndWait(std::string nameID) {
  std::unique_lock<std::mutex> l(mutex_);

  if (cancelFunctionWithLock(l, nameID)) {
    runningCondvar_.wait(l, [this]() { return !cancellingCurrentFunction_; });
    return true;
  }

  auto it = functionsMap_.find(nameID);
  if (it != functionsMap_.end() && it->second->isValid()) {
    cancelFunction(l, it->second);
    return true;
  }
  return false;
}

void FunctionScheduler::cancelFunction(const std::unique_lock<std::mutex>& l,
                                       RepeatFunc* it) {
  // This function should only be called with mutex_ already locked.
  assert(l.mutex() == &mutex_);
  assert(l.owns_lock());
  static_cast<void>(functionsMap_.erase(it->name));
  it->cancel();
}

bool FunctionScheduler::cancelAllFunctionsWithLock(
    const std::unique_lock<std::mutex>& lock) {
  assert(lock.owns_lock() == true);
  functions_.clear();
  functionsMap_.clear();
  if (currentFunction_) {
    cancellingCurrentFunction_ = true;
  }
  currentFunction_ = nullptr;
  return cancellingCurrentFunction_;
}

void FunctionScheduler::cancelAllFunctions() {
  std::unique_lock<std::mutex> l(mutex_);
  static_cast<void>(cancelAllFunctionsWithLock(l));
}

void FunctionScheduler::cancelAllFunctionsAndWait() {
  std::unique_lock<std::mutex> l(mutex_);
  if (cancelAllFunctionsWithLock(l)) {
    runningCondvar_.wait(l, [this]() { return !cancellingCurrentFunction_; });
  }
}

bool FunctionScheduler::resetFunctionTimer(std::string nameID) {
  std::unique_lock<std::mutex> l(mutex_);
  if (currentFunction_ != nullptr && currentFunction_->name == nameID) {
    if (cancellingCurrentFunction_ || currentFunction_->runOnce) {
      return false;
    }
    currentFunction_->resetNextRunTime(steady_clock::now());
    return true;
  }

  // Since __adjust_heap() isn't a part of the standard API, there's no way to
  // fix the heap ordering if we adjust the key (nextRunTime) for the existing
  // RepeatFunc. Instead, we just cancel it and add an identical object.
  auto it = functionsMap_.find(nameID);
  if (it != functionsMap_.end() && it->second->isValid()) {
    if (running_) {
      it->second->resetNextRunTime(steady_clock::now());
      std::make_heap(functions_.begin(), functions_.end(), fnCmp_);
      runningCondvar_.notify_one();
    }
    return true;
  }
  return false;
}

bool FunctionScheduler::start() {
  std::unique_lock<std::mutex> l(mutex_);
  if (running_) {
    return false;
  }

  auto now = steady_clock::now();
  // Reset the next run time. for all functions.
  // note: this is needed since one can shutdown() and start() again
  for (const auto& f : functions_) {
    f->resetNextRunTime(now);
  }
  std::make_heap(functions_.begin(), functions_.end(), fnCmp_);

  thread_ = std::thread([&]() { this->run(); });
  running_ = true;

  return true;
}

bool FunctionScheduler::shutdown() {
  {
    std::lock_guard<std::mutex> g(mutex_);
    if (!running_) {
      return false;
    }

    running_ = false;
    runningCondvar_.notify_one();
  }
  thread_.join();
  return true;
}

void FunctionScheduler::run() {
  std::unique_lock<std::mutex> lock(mutex_);

  // folly::setThreadName(threadName_);

  while (running_) {
    // If we have nothing to run, wait until a function is added or until we
    // are stopped.
    if (functions_.empty()) {
      runningCondvar_.wait(lock);
      continue;
    }

    auto now = steady_clock::now();

    // Move the next function to run to the end of functions_
    std::pop_heap(functions_.begin(), functions_.end(), fnCmp_);

    // Check to see if the function was cancelled.
    // If so, just remove it and continue around the loop.
    if (!functions_.back()->isValid()) {
      functions_.pop_back();
      continue;
    }

    auto sleepTime = functions_.back()->getNextRunTime() - now;
    if (sleepTime < microseconds::zero()) {
      // We need to run this function now
      runOneFunction(lock, now);
      runningCondvar_.notify_all();
    } else {
      // Re-add the function to the heap, and wait until we actually
      // need to run it.
      std::push_heap(functions_.begin(), functions_.end(), fnCmp_);
      static_cast<void>(runningCondvar_.wait_for(lock, sleepTime));
    }
  }
}

void FunctionScheduler::runOneFunction(std::unique_lock<std::mutex>& lock,
                                       steady_clock::time_point now) {
  assert(lock.mutex() == &mutex_);
  assert(lock.owns_lock());

  // The function to run will be at the end of functions_ already.
  //
  // Fully remove it from functions_ now.
  // We need to release mutex_ while we invoke this function, and we need to
  // maintain the heap property on functions_ while mutex_ is unlocked.
  auto func = std::move(functions_.back());
  functions_.pop_back();
  if (func->cb == nullptr) {
    return;
  }
  currentFunction_ = func.get();
  // Update the function's next run time.
  if (steady_) {
    // This allows scheduler to catch up
    func->setNextRunTimeSteady();
  } else {
    // Note that we set nextRunTime based on the current time where we started
    // the function call, rather than the time when the function finishes.
    // This ensures that we call the function once every time interval, as
    // opposed to waiting time interval seconds between calls.  (These can be
    // different if the function takes a significant amount of time to run.)
    func->setNextRunTimeStrict(now);
  }

  // Release the lock while we invoke the user's function
  lock.unlock();

  // Invoke the function
  try {
    func->cb();
  } catch (const std::exception& ex) {
    
  }

  // Re-acquire the lock
  lock.lock();

  if (currentFunction_ == nullptr) {
    // The function was cancelled while we were running it.
    // We shouldn't reschedule it;
    cancellingCurrentFunction_ = false;
    return;
  }
  if (currentFunction_->runOnce) {
    // Don't reschedule if the function only needed to run once.
    static_cast<void>(functionsMap_.erase(currentFunction_->name));
    currentFunction_ = nullptr;
    return;
  }

  // Re-insert the function into our functions_ heap.
  // We only maintain the heap property while running_ is set.  (running_ may
  // have been cleared while we were invoking the user's function.)
  functions_.push_back(std::move(func));

  // Clear currentFunction_
  currentFunction_ = nullptr;

  if (running_) {
    std::push_heap(functions_.begin(), functions_.end(), fnCmp_);
  }
}

void FunctionScheduler::addFunctionToHeap(
    const std::unique_lock<std::mutex>& lock,
    std::unique_ptr<RepeatFunc> func) {
  // This function should only be called with mutex_ already locked.
  assert(lock.mutex() == &mutex_);
  assert(lock.owns_lock());

  functions_.push_back(std::move(func));
  functionsMap_[functions_.back()->name] = functions_.back().get();
  if (running_) {
    functions_.back()->resetNextRunTime(steady_clock::now());
    std::push_heap(functions_.begin(), functions_.end(), fnCmp_);
    // Signal the running thread to wake up and see if it needs to change
    // its current scheduling decision.
    runningCondvar_.notify_one();
  }
}

void FunctionScheduler::setThreadName(std::string threadName) {
  std::unique_lock<std::mutex> l(mutex_);
  threadName_ = threadName;
}

}  // namespace folly
