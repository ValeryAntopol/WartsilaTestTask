#include "RequestProcessor.h"

#include <cassert>
#include <chrono>
#include <iostream>

void RequestProcessor::start(size_t numberOfProcessorThreads) {
  stopper.reset();
  for (size_t i = 0; i < numberOfProcessorThreads; i++) {
    workers.emplace_back([this]() {workerThread(); });
  }

  getter = std::thread([this]() {getterThread(); });
}

void RequestProcessor::stop() {
  stopper.stop();
  cv.notify_all();
  for (auto& thread : workers) {
    thread.join();
  }

  getter.join();
  workers.clear();
  while (!requests.empty()) {
    requests.pop();
  }
}

void RequestProcessor::getterThread() {
  while (!stopper.isStopped()) {
    auto request = GetRequest(stopper);
    if (request == nullptr) {
      break;
    }

    {
      std::lock_guard<std::mutex> guard(requestsMutex);
      requests.emplace(request);
    }

    cv.notify_one();
  }
}

void RequestProcessor::workerThread() {
  std::unique_ptr<Request> request;
  while (true) {
    {
      std::unique_lock<std::mutex> queueLock(requestsMutex);
      cv.wait(queueLock, [this]() {
        return stopper.isStopped() || requests.size() > 0;
        });
      if (stopper.isStopped()) {
        break;
      }

      request = std::move(requests.front());
      requests.pop();
    }

    ProcessRequest(request.get(), stopper);
  }
}