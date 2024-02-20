#include <iostream>
#include <vector>

#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
  friend class Solver;

private:
  std::vector<std::vector<double>> _data;
  int _size;

public:
  Matrix(int size);
  int get_size() const;
  double &get(size_t x, size_t y);
};

const std::ostream &operator<<(std::ostream &os, Matrix &matrix);

#endif
