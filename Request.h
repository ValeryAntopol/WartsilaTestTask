#pragma once

#include "StopperImpl.h"

#include <cstdint>

class Request {
public:
  ~Request();

private:
  int padding;
};

Request* GetRequest(Stopper stopSignal);
void ProcessRequest(Request* request, Stopper stopSignal);
void printTestResults();
