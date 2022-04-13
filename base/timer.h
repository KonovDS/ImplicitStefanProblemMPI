#ifndef IMPLICITSTEFANPROBLEMMPI_BASE_TIMER_H_
#define IMPLICITSTEFANPROBLEMMPI_BASE_TIMER_H_

#include <chrono>
#include <utility>
#include <vector>
#include <string>

#include <iostream>

#include "print.h"

class Timer {
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, std::string>> points;
 public:
  Timer();
  void AddMeasurment(const char *str);
  void Print();
};

#endif //IMPLICITSTEFANPROBLEMMPI_BASE_TIMER_H_
