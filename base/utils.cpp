//
// Created by user on 7 апр. 2022 г..
//
#include "utils.h"

#include <mpi.h>

bool IsMainMPINode() {
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  return world_rank == 0;
}