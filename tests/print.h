#ifndef IMPLICITSTEFANPROBLEMMPI_TESTS_PRINT_H_
#define IMPLICITSTEFANPROBLEMMPI_TESTS_PRINT_H_

#include <mpi.h>

#include <iostream>
#include <string>

template <class T, class = std::enable_if_t<(std::is_same_v<T, const char>)>>
std::string ToStr(T *x) {
  return std::string(x);
}

template <class T, class = std::enable_if_t<(std::is_same_v<T, int>)>>
std::string ToStr(T x) {
  return std::to_string(x);
}

template <class... Args>
void Print(Args... args) {
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_rank == 0) {
    std::string str = (ToStr(args) + ...) + "\n";
    std::cerr << str;
  }
}

template <class... Args>
void PrintAll(Args... args) {
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  std::string str = "[" + std::to_string(world_rank) + "]" + (ToStr(args) + ...) + "\n";
  std::cerr << str;
}


#endif //IMPLICITSTEFANPROBLEMMPI_TESTS_PRINT_H_
