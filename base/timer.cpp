#include "timer.h"

#include <chrono>
#include <utility>
#include <vector>
#include <string>

#include "print.h"

void Timer::AddMeasurment(const char *str) {
  points.emplace_back(std::chrono::high_resolution_clock::now(), std::string(str));
}

Timer::Timer() {
  start = std::chrono::high_resolution_clock::now();
}

void Timer::Print() {
  std::string line;
  for (int i = 0; i < 60; i++) {
    line += '=';
  }
  ::Print(line);
  ::Print("Stats:");
  auto prev = start;
  for (auto &i : points) {
    auto s = std::chrono::duration_cast<std::chrono::seconds>(i.first - prev);
    ::Print("   ", s.count(), " s : ", i.second);
    prev = i.first;
  }
  auto s = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
  ::Print("Total = ", s.count(), " s");
  ::Print(line);
}