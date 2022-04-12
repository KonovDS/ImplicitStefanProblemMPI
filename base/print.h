#ifndef IMPLICITSTEFANPROBLEMMPI_UTILS_PRINT_H_
#define IMPLICITSTEFANPROBLEMMPI_UTILS_PRINT_H_

#include <mpi.h>

#include <iostream>
#include <string>

#include "utils.h"

// Initializatoion in .h won't work unless inlined
inline std::string ToStr(const char *x) {
  return std::string(x);
}

inline std::string ToStr(int x) {
  return std::to_string(x);
}

inline std::string ToStr(double x) {
  return std::to_string(x);
}

template <class... Args>
void Print(Args... args) {
  if (IsMainMPINode()) {
    std::string str = (ToStr(args) + ...) + "\n";
    std::cout << str;
  }
}

template <class... Args>
void PrintAll(Args... args) {
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  std::string str = "[" + std::to_string(world_rank) + "]" + (ToStr(args) + ...) + "\n";
  std::cout << str;
}

#endif //IMPLICITSTEFANPROBLEMMPI_UTILS_PRINT_H_
