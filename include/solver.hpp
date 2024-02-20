#include "matrix.hpp"

#pragma once

#ifndef SOLVER_HPP
#define SOLVER_HPP

class Solver {
  friend class Matrix;

private:
  Matrix _matrix;
  double _precision;
  std::vector<double> _values;
  std::vector<double> _approximation;
  std::vector<double> _deviation;

public:
  Solver(const Matrix &matrix, const std::vector<double> &values, double precision);
  void process();
  bool make_diagonal_dominant();
};

#endif
