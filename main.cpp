#include <iostream>

#include "basic_parabolic.h"

template <class... Args>
double zero(Args... args) {
  return 0;
}

double f(double x, double y, double t) {
  return 1000 * sin(M_PI * x) * sin(M_PI * y) * exp(-2 * M_PI * M_PI * t);
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
  BasicParabolic parabolic(100, 100, 0.01, 0.01, 1);
  parabolic.SetupTau();
  parabolic.SetupInitial(init);
  parabolic.SetupBorders(zero, zero, zero, zero);
  parabolic.Run(double(0.5));
  std::cout << parabolic.L0Partial(mid) << std::endl;
  parabolic.Run(double(0.5));
  std::cout << parabolic.L0Partial(fin) << std::endl;
  MPI_Finalize();
  return 0;
}