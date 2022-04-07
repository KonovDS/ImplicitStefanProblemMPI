#ifndef IMPLICITSTEFANPROBLEMMPI_MESH_MPI_MESH_H_
#define IMPLICITSTEFANPROBLEMMPI_MESH_MPI_MESH_H_

#include "mesh.h"

#include <mpi.h>

#include <stdexcept>
#include <iostream>

class NoMPIException : std::exception {
  const char * what() const noexcept override {
    return "MPI was not initialized correctly";
  }
};

class MPIRecvError : std::exception {
  const char * what() const noexcept override {
    return "MPI Recv failed";
  }
};

class MPISendError : std::exception {
  const char * what() const noexcept override {
    return "MPI Send failed";
  }
};

class MPISendLogicError : std::exception {
  const char * what() const noexcept override {
    return "Attempt sending to self rank";
  }
};

template<class T>
class MPIMesh : public Mesh<T> {
  int rank_, world_size_;
 public:
  MPIMesh(size_t individual_k, size_t l) : Mesh<T>(individual_k, l) { //NOLINT
    if (MPI_Comm_size(MPI_COMM_WORLD, &world_size_) != MPI_SUCCESS)
      throw NoMPIException();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
  }

  inline void SendLeft() {
    auto d = this->LeftPtrSend();
    auto size = this->BorderLen() * sizeof(T);
    auto tag = 0;
    auto dest = rank_ - 1;
    if (MPI_Send((void *)d, size, MPI_BYTE, dest, tag, MPI_COMM_WORLD) != MPI_SUCCESS)
      throw MPISendError();
  }

  inline void SendRight() {
    auto d = this->RightPtrSend();
    auto size = this->BorderLen() * sizeof(T);
    auto tag = 0;
    auto dest = rank_ + 1;
    if (MPI_Send((void *)d, size, MPI_BYTE, dest, tag, MPI_COMM_WORLD) != MPI_SUCCESS)
      throw MPISendError();
  }

  inline void RecvLeft() {
    auto d = this->LeftPtrRecv();
    auto size = this->BorderLen() * sizeof(T);
    auto tag = MPI_ANY_TAG;
    auto src = rank_ - 1;
    MPI_Status status;
    if (MPI_Recv((void *)d, size, MPI_BYTE, src, tag, MPI_COMM_WORLD, &status) != MPI_SUCCESS)
      throw MPIRecvError();
  }

  inline void RecvRight() {
    auto d = this->RightPtrRecv();
    auto size = this->BorderLen() * sizeof(T);
    auto tag = MPI_ANY_TAG;
    auto src = rank_ + 1;
    MPI_Status status;
    if (MPI_Recv((void *)d, size, MPI_BYTE, src, tag, MPI_COMM_WORLD, &status) != MPI_SUCCESS)
      throw MPIRecvError();
  }

  inline void Update() {
    if (rank_ != world_size_ - 1) {
      SendRight();
      RecvRight();
    }
    if (rank_ != 0) {
      SendLeft();
      RecvLeft();
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  bool IsLeftBorder() {
    return rank_ == 0;
  }

  bool IsRightBorder() {
    return rank_ == world_size_ - 1;
  }

  size_t GlobalI(size_t i) {
    return world_size_ * (this->DimK() - 1) + i;
  }

  void CompleteSend(size_t rank) {
    if (rank == rank_) {
      auto d = &(this->At(0, 0));
      auto size = this->dimK() * this->dimL() * sizeof(T);
      auto tag = 0;
      auto dest = rank;
      if (MPI_Send((void *)d, size, MPI_BYTE, dest, tag, MPI_COMM_WORLD) != MPI_SUCCESS)
        throw MPISendError();
    } else {
      throw MPISendLogicError();
    }
  }
};

#endif //IMPLICITSTEFANPROBLEMMPI_MESH_MPI_MESH_H_
