#include <iostream>

#include "RequestProcessor.h"

int main() {
  const int WORKER_THREAD_COUNT = 5;
  const std::chrono::milliseconds WORK_TIME(30000);
  RequestProcessor requestProcessor;
  requestProcessor.start(WORKER_THREAD_COUNT);
  std::this_thread::sleep_for(WORK_TIME);
  requestProcessor.stop();
  std::cout
    << "Worker thread count: " << WORKER_THREAD_COUNT << std::endl
    << "Work time: " << std::chrono::duration<double>(WORK_TIME).count() << "s" << std::endl;
  printTestResults();
}
