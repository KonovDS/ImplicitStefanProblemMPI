#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "mpi_mesh.h"

#include <mpi.h>

#include <string>

#include "print.h"

TEST_CASE("MPI mesh test", "[mpi][mpi_mesh]") {
  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int kSize = 10;
  MPI_Barrier(MPI_COMM_WORLD);
  MPIMesh<int> m(kSize, kSize);
  MPI_Barrier(MPI_COMM_WORLD);
  for (int i = 0; i < kSize; i++) {
    for (int j = 0; i < kSize; i++) {
      m.At(i, j) = world_rank;
    }
  }

  m.Update();

  if (world_rank != 0) {
    CHECK(m.At(0,0) == world_rank - 1);
  } else {
    CHECK(m.At(0,0) == world_rank);
  }

  if (world_rank != world_size - 1) {
    CHECK(m.At(kSize - 1,0) == world_rank + 1);
  } else {
    CHECK(m.At(kSize - 1,0) == world_rank);
  }

  PrintAll("[MPI mesh test] ", "At(0,0)=", m.At(0,0), ", At(kSize - 1,0)=", m.At(kSize - 1,0));
}