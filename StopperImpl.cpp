#include "StopperImpl.h"

StopperImpl::StopperImpl() : controlVariable(false) {}

bool StopperImpl::isStopped() {
  return controlVariable.load();
}

void StopperImpl::stop() {
  controlVariable.store(true);
}

void StopperImpl::reset() {
  controlVariable.store(false);
}
