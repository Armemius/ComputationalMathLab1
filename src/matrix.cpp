#include "matrix.hpp"
#include <stdexcept>

Matrix::Matrix(int size)
    : _size(size), _data(std::vector<std::vector<double>>(
                       size, std::vector<double>(size))) {}

int Matrix::get_size() const { return this->_size; }

double &Matrix::get(size_t x, size_t y) {
  if (x > this->_size || y > this->_size || x < 0 || y < 0) {
    throw std::out_of_range("Value is out of bounds");
  }
  return this->_data[x][y];
}

const std::ostream &operator<<(std::ostream &os, Matrix &matrix) {
  for (size_t it = 0; it < matrix.get_size(); ++it) {
    for (size_t jt = 0; jt < matrix.get_size(); ++jt) {
        os << matrix.get(it, jt) << " ";
    }
    os << std::endl;
  }

  return os;
}