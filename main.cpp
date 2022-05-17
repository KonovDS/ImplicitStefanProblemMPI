#include <iostream>

#include "basic_parabolic.h"

#include "print.h"
#include "timer.h"

const double kH = 0.001;
const double kTime = 0.1;

template <class... Args>
double zero(Args... args) {
  return 0;
}

double f(double x, double y, double t) {
  return 10000 * sin(M_PI * x) * sin(M_PI * y) * exp(-2 * M_PI * M_PI * t);
}

double init(size_t i, size_t j) {
  return f(i*kH, j*kH, 0);
}

double fin(size_t i, size_t j) {
  return f(i*kH, j*kH, kTime);
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  BasicParabolic parabolic(100 / world_size, 100, kH, kH, 1);
  parabolic.SetupBorders(zero, zero, zero, zero);

  Timer tt;

  auto t = parabolic.SetupTau();
  Print("[Basic parabolic test] ", "tau = ", t);
  parabolic.SetupInitial(init);
  PrintAll("[Basic parabolic test] ", "Computed L0 debug ", parabolic.L0Partial(init));
  PrintAll("[Basic parabolic test] ", "Computed L0 debug ", parabolic.L0Partial(fin));
  parabolic.Run(double(kTime));
  PrintAll("[Basic parabolic test] ", "Computed L0 error at t=", kTime ," is ", parabolic.L0Partial(fin));

  tt.AddMeasurment("Finished 1 task");

  parabolic.SetupTau(t/2);

  parabolic.SetupInitial(init);
  parabolic.Run(double(kTime));
  PrintAll("[Basic parabolic test] ", "Computed L0 error at t=", kTime ," is ", parabolic.L0Partial(fin));

  tt.AddMeasurment("Finished 2 task");

  parabolic.SetupTau(t/4);
  parabolic.SetupInitial(init);
  parabolic.Run(double(kTime));
  PrintAll("[Basic parabolic test] ", "Computed L0 error at t=", kTime ," is ", parabolic.L0Partial(fin));

  tt.AddMeasurment("Finished 3 task");

  tt.Print();

  MPI_Finalize();
  return 0;
}