#include "Request.h"

#include <iostream>
#include <mutex>

namespace {
  std::mutex testerMutex;
  uint32_t getRequestCount = 0;
  uint32_t deleteRequestCount = 0;
  uint32_t processRequestCount = 0;
  const std::chrono::milliseconds GET_REQUEST_DURATION(10);
  const std::chrono::milliseconds PROCESS_REQUEST_DURATION(100);

  void registerGetRequest(Request* request) {
    std::lock_guard<std::mutex> guard(testerMutex);
    getRequestCount++;
  }

  void registerProcessRequest(Request* request) {
    std::lock_guard<std::mutex> guard(testerMutex);
    processRequestCount++;
  }
}

Request::~Request() {
  deleteRequestCount++;
}

void printTestResults() {
  std::cout
    << "GetRequest duration: " << std::chrono::duration<double>(GET_REQUEST_DURATION).count() << "s" << std::endl
    << "ProcessRequest duration: " << std::chrono::duration<double>(PROCESS_REQUEST_DURATION).count() << "s" << std::endl
    << "Test results:" << std::endl
    << "Requests got: " << getRequestCount << std::endl
    << "Requests processed: " << processRequestCount << std::endl
    << "Requests deleted: " << deleteRequestCount << std::endl;
}

Request* GetRequest(Stopper stopSignal) {
  Request* request = nullptr;
  std::this_thread::sleep_for(GET_REQUEST_DURATION);
  if (!stopSignal.get().isStopped()) {
    request = new Request;
    registerGetRequest(request);
  }

  return request;
}

void ProcessRequest(Request* request, Stopper stopSignal) {
  if (stopSignal.get().isStopped()) {
    return;
  }

  std::this_thread::sleep_for(PROCESS_REQUEST_DURATION);
  registerProcessRequest(request);
}
