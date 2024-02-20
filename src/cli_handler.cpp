#include "cli_handler.hpp"
#include "matrix.hpp"
#include "solver.hpp"
#include <iostream>

void run_cli() {
  double precision;
  std::cout << "Enter precision: ";
  std::cin >> precision;
  int size;
  std::cout << "Enter matrix size: ";
  std::cin >> size;
  Matrix mat(size);
  std::vector<double> values(size);
  std::cout << "Enter matrix elements: " << std::endl;
  for (size_t it = 0; it < size; ++it) {
    for (size_t jt = 0; jt < size; ++jt) {
      std::cin >> mat.get(it, jt);
    }
    double value;
    std::cin >> value;
    values[it] = value;
  }
  auto solver = Solver(mat, values, precision);
  solver.process();
}
