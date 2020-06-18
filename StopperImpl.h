#pragma once

#include <atomic>

class StopperImpl {
public:
  StopperImpl();

  bool isStopped();
  void stop();
  void reset();

private:
  std::atomic<bool> controlVariable;
};

using Stopper = std::reference_wrapper<StopperImpl>;
