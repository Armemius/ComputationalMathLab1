#include "file_handler.hpp"
#include "solver.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void run_file(char *filename) {
  std::ifstream infile(filename);
  std::string line;
  if (!infile.is_open()) {
    throw std::exception("Unable to open file");
  }
  double precision;
  if (!(infile >> precision)) {
    throw std::exception("Unexpected EOF");
  }
  int size;
  if (!(infile >> size)) {
    throw std::exception("Unexpected EOF");
  }
  Matrix mat(size);
  std::vector<double> values(size);
  for (size_t it = 0; it < size; ++it) {
    for (size_t jt = 0; jt < size; ++jt) {
      if (!(infile >> mat.get(it, jt))) {
        throw std::exception("Unexpected EOF");
      }
    }
    double value;
    if (!(infile >> value)) {
        throw std::exception("Unexpected EOF");
      }
    values[it] = value;
  }
  auto solver = Solver(mat, values, precision);
  solver.process();
}