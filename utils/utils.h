#ifndef IMPLICITSTEFANPROBLEMMPI_UTILS_UTILS_H_
#define IMPLICITSTEFANPROBLEMMPI_UTILS_UTILS_H_

#include <mpi.h>

bool IsMainMPINode() {
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  return world_rank == 0;
}

#endif //IMPLICITSTEFANPROBLEMMPI_UTILS_UTILS_H_
