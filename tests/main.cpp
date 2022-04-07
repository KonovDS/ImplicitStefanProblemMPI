#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "mpi_helpers.h"
#include <sstream>

// https://stackoverflow.com/a/62537883/10096003
int main(int argc, char *argv[]) {
  MPI_Init_H autoInit{argc, argv}; // calls MPI_Finalize() on destruction

  std::stringstream ss;

  /* save old buffer and redirect output to string stream */
  auto cout_buf = std::cout.rdbuf(ss.rdbuf());

  int result = Catch::Session().run(argc, argv);

  /* reset buffer */
  std::cout.rdbuf(cout_buf);

  MPI_Comm_H world{MPI_COMM_WORLD};

  std::stringstream printRank;
  printRank << "Rank ";
  printRank.width(2);
  printRank << std::right << world.rank() << ":\n";

  for (int i{1}; i < world.size(); ++i) {
    MPI_Barrier(world);
    if (i == world.rank()) {
      /* if all tests are passed, it's enough if we hear that from
       * the master. Otherwise, print results */
      if (ss.str().rfind("All tests passed") == std::string::npos)
        std::cout << printRank.str() + ss.str();
    }
  }
  /* have master print last, because it's the one with the most assertions */
  MPI_Barrier(world);
  if (world.isMaster())
    std::cout << printRank.str() + ss.str();

  return result;
}