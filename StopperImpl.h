#pragma once

#include <mutex>

class StopperImpl {
public:
  StopperImpl();

  bool isStopped();
  void stop();
  void reset();

private:
  bool controlVariable;
  std::mutex mutex;
};

using Stopper = std::reference_wrapper<StopperImpl>;
