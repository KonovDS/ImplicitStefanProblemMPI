#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include <iostream>

#include <mpi.h>
#include <omp.h>

TEST_CASE("OpenMP test", "[omp]") {
  std::cerr << "OPENMP version = " <<_OPENMP << std::endl;
  CHECK(_OPENMP >= 201511);
}

TEST_CASE("MPI test", "[mpi]") {
  // Initialize the MPI environment
  int ret = MPI_Init(NULL, NULL);
  CHECK(ret == 0);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Print off a hello world message
  std::cerr << "MPI running on " << processor_name << ", rank " << world_rank << " out of " << world_size << std::endl;

  // Finalize the MPI environment.
  ret = MPI_Finalize();
  CHECK(ret == 0);
}