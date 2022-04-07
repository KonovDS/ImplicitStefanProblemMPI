#include <iostream>

#include "basic_parabolic.h"

#include "print.h"

template <class... Args>
double zero(Args... args) {
  return 0;
}

double f(double x, double y, double t) {
  return 10000 * sin(M_PI * x) * sin(M_PI * y) * exp(-2 * M_PI * M_PI * t);
}

double init(size_t i, size_t j) {
  return f(i*0.01, j*0.01, 0);
}

double mid(size_t i, size_t j) {
  return f(i*0.01, j*0.01, 0.5);
}

double fin(size_t i, size_t j) {
  return f(i*0.01, j*0.01, 1);
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  BasicParabolic parabolic(20, 100, 0.01, 0.01, 1);
  parabolic.SetupTau();
  parabolic.SetupInitial(init);
  parabolic.SetupBorders(zero, zero, zero, zero);
  parabolic.Run(double(0.5));
  PrintAll("[Basic parabolic test] ", "Computed L0 error at t=", 0.5 ," is ", parabolic.L0Partial(mid));
  parabolic.Run(double(0.5));
  PrintAll("[Basic parabolic test] ", "Computed L0 error at t=", 1.0 ," is ", parabolic.L0Partial(fin));
  MPI_Finalize();
  return 0;
}