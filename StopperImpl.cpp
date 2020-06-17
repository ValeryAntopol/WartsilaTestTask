#include "StopperImpl.h"

StopperImpl::StopperImpl() : controlVariable(false) {}

bool StopperImpl::isStopped() {
  std::lock_guard<std::mutex> guard(mutex);
  auto result = controlVariable;
  return result;
}

void StopperImpl::stop() {
  std::lock_guard<std::mutex> guard(mutex);
  controlVariable = true;
}

void StopperImpl::reset() {
  controlVariable = false;
}
