#ifndef __GAEventNofifierTest_HPP__
#define __GAEventNofifierTest_HPP__

#include <iostream>
#include "GA/include/Notifier.hpp"

#define LOG(v) std::cout << v << "\r\n"

template <typename T>
bool GAEventNofifierTest(T lastValue, T value) {
  Notifier<T> notifier;

  bool isLastValueEquals = false;
  bool isValueEquals = false;
  bool isMeet = false;

  // test onChanged
  isLastValueEquals = false;
  isValueEquals = false;
  isMeet = false;
  notifier += [&](T lv, T v) {
    isLastValueEquals = lv == lastValue;
    isValueEquals = v == value;
  };

  notifier.invoke(lastValue, value);
  if (!isLastValueEquals) {
    LOG("onChanged failed: last value not equals.");
    return false;
  }

  if (!isValueEquals) {
    LOG("onChanged failed: value not equals.");
    return false;
  }
  LOG("watch onChanged passed.");

  // test onChanged clear
  isLastValueEquals = false;
  isValueEquals = false;
  notifier.clear();
  notifier.invoke(lastValue, value);
  if (isLastValueEquals || isValueEquals) {
    LOG("onChanged failed: failed to clear.");
    return false;
  }
  LOG("watch onChanged clear passed.");

  // test watch validator.
  isLastValueEquals = false;
  isValueEquals = false;
  notifier.watch(
      [&](T lv, T v) {
        isLastValueEquals = lv == lastValue;
        isValueEquals = v == value;
        return false;
      },
      [&](T lv, T v) {

      });

  notifier.invoke(lastValue, value);
  if (!isLastValueEquals) {
    LOG("watch validator failed: last value not equals.");
    return false;
  }

  if (!isValueEquals) {
    LOG("watch validator failed: value not equals.");
    return false;
  }
  LOG("watch watch validator passed.");

  // test watch clear
  notifier.clearWatchers();
  isLastValueEquals = false;
  isValueEquals = false;

  notifier.invoke(lastValue, value);
  if (isLastValueEquals || isValueEquals) {
    LOG("watch clear failed.");
    return false;
  }
  LOG("watch watch clear passed.");

  // test watch handler: not meet
  notifier.clearWatchers();

  isLastValueEquals = false;
  isValueEquals = false;
  isMeet = false;
  notifier.watch(
      [&](T lv, T v) {
        isLastValueEquals = lv == lastValue;
        isValueEquals = v == value;
        return false;
      },
      [&](T lv, T v) { isMeet = true; });

  notifier.invoke(lastValue, value);
  if (!isLastValueEquals) {
    LOG("watch handler not meet failed: validator last value not equals.");
    return false;
  }

  if (!isValueEquals) {
    LOG("watch handler not meet failed: validator value not equals.");
    return false;
  }

  if (isMeet) {
    LOG("watch handler not meet failed: isMeet return true when not meet.");
    return false;
  }
  LOG("watch handler not meet passed.");

  // test watch handler: meet
  notifier.clearWatchers();

  isLastValueEquals = false;
  isValueEquals = false;
  isMeet = false;
  notifier.watch(
      [&](T lv, T v) {
        isLastValueEquals = lv == lastValue;
        isValueEquals = v == value;
        return true;
      },
      [&](T lv, T v) { isMeet = true; });

  notifier.invoke(lastValue, value);
  if (!isLastValueEquals) {
    LOG("watch handler meet failed: validator last value not equals.");
    return false;
  }

  if (!isValueEquals) {
    LOG("watch handler meet failed: validator value not equals.");
    return false;
  }

  if (!isMeet) {
    LOG("watch handler meet failed: isMeet return true when not meet.");
    return false;
  }

  LOG("watch handler meet passed.");


  LOG("All test is passed, returning true");
  return true;
}

#endif