#ifndef IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_
#define IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_

#include "mpi_mesh.h"

#include <stdexcept>
#include <cmath>

class IncompleteTask : std::exception {
 public:
  const char * what() const noexcept override {
    return "Unable to launch BasicParabolic Task with incomplete settings.";
  }
};

class BasicParabolic {
  MPIMesh<double> before, after;
  double a, tau, h_x, h_y;
  struct {
    double (*l)(size_t j, const MPIMesh<double> &b) = nullptr;
    double (*r)(size_t j, const MPIMesh<double> &b) = nullptr;
    double (*t)(size_t global_i, const MPIMesh<double> &b) = nullptr;
    double (*b)(size_t global_i, const MPIMesh<double> &b) = nullptr;
  } borders;

  void ExplicitScheme(size_t i, size_t j);
  void Step();
  void Compute(size_t steps);
  void Border();
  inline static double AutoTau(double h, double a) {
    return h * h / (2 * a);
  }

 public:
  BasicParabolic(size_t individual_k, size_t l,
                 double h_x, double h_y,
                 double a) :
                 before(individual_k, l), after(individual_k, l) {
    this->a = a;
    this->tau = 0;
    this->h_x = h_x;
    this->h_y = h_y;
  }
  void Run(double t);
  void Run(size_t s);
  double SetupTau(double t = 0);
  inline void SetupBorders(double (*l)(size_t j, const MPIMesh<double> &b),
                    double (*r)(size_t j, const MPIMesh<double> &b),
                    double (*t)(size_t global_i, const MPIMesh<double> &b),
                    double (*b)(size_t global_i, const MPIMesh<double> &b)) {
    borders.l = l;
    borders.r = r;
    borders.t = t;
    borders.b = b;
  }
  void SetupInitial(double (*init)(size_t global_i, size_t j));
  double L2Partial(double (*f)(size_t global_i, size_t j));
  double L0Partial(double (*f)(size_t global_i, size_t j));
  void PrintOut();
};

#endif //IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_
