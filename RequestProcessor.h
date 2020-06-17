#pragma once

#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "Request.h"

class RequestProcessor
{
public:
  RequestProcessor() = default;
  void start(size_t n);
  void stop();

private:
  void getterThread();
  void workerThread();

  std::condition_variable cv;
  std::thread getter;
  std::mutex requestsMutex;
  std::queue<std::unique_ptr<Request>> requests;
  StopperImpl stopper;
  std::vector<std::thread> workers;
};
