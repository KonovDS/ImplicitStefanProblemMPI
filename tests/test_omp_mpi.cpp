#define CATCH_CONFIG_FAST_COMPILE
#include "lib/catch.hpp"

#include <iostream>

#include <mpi.h>
#include <omp.h>

#include "print.h"

TEST_CASE("OpenMP basic test", "[omp]") {
  Print("[OpenMP basic test] ", "OPENMP version = ", _OPENMP);
  CHECK(_OPENMP >= 201511);
}

TEST_CASE("OpenMP for test", "[omp]") {
  Print("[OpenMP for test] ", "omp_get_max_threads() = ", omp_get_max_threads());
  bool threads[omp_get_max_threads()];
  for (int i = 0; i < omp_get_max_threads(); i++) {
    threads[i] = false;
  }
  #pragma omp parallel for default(none) shared(threads) schedule(static)
  for (int i = 0; i < omp_get_max_threads(); i++) {
      threads[i] = true;
  }
  for (int i = 0; i < omp_get_max_threads(); i++) {
    CHECK(threads[i] == true);
  }
}

TEST_CASE("MPI basic test", "[mpi]") {
  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_size != 1) {
    if (world_rank == 0) {
      int data = 13; // arbitrary number
      for (int i = 1; i < world_size; i++) {
        CHECK(MPI_Send(&data, 1, MPI_INT32_T, i, 0, MPI_COMM_WORLD) == MPI_SUCCESS);
      }
    } else {
      int data = 0;
      MPI_Status status;
      CHECK(MPI_Recv(&data, 1, MPI_INT32_T, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status) == MPI_SUCCESS);
      CHECK(data == 13);
    }
  } else {
    Print("[MPI basic test] ","Unable to test MPI functionality. Consider running MPI with -n 2 or more");
  }
}