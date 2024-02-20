#include "solver.hpp"
#include <vector>

Solver::Solver(const Matrix &matrix, const std::vector<double> &values,
               double precision)
    : _matrix(matrix), _values(values), _precision(precision),
      _approximation(std::vector<double>(matrix.get_size())),
      _deviation(std::vector<double>(matrix.get_size())) {}

void Solver::process() {
  if (!this->make_diagonal_dominant()) {
    std::cout << "Unable to make matrix diagonally dominant" << std::endl;
    return;
  }

  // Calculate zero approximation
  for (size_t it = 0; it < this->_matrix.get_size(); ++it) {
    this->_approximation[it] = this->_values[it] / this->_matrix.get(it, it);
  }

  bool is_ready;
  int iterations = 0;
  // Calculate approximations
  do {
    std::cout << "Iteration number: " << iterations << std::endl;
    std::cout << "Current approximations (";
    for (size_t it = 0; it < this->_approximation.size(); ++it) {
      std::cout << "X" << it << ": " << this->_approximation[it];
      if (it != this->_approximation.size() - 1) {
        std::cout << "; ";
      }
    }
    std::cout << ")" << std::endl;
    std::cout << "Current deviations (";
    for (size_t it = 0; it < this->_deviation.size(); ++it) {
      std::cout << "D" << it << ": " << this->_deviation[it];
      if (it != this->_deviation.size() - 1) {
        std::cout << "; ";
      }
    }
    std::cout << ")" << std::endl << std::endl;
    ++iterations;
    std::vector<double> new_approximation(this->_matrix.get_size());
    for (size_t it = 0; it < this->_matrix.get_size(); ++it) {
      double sum = _values[it];
      for (size_t jt = 0; jt < this->_matrix.get_size(); ++jt) {
        if (it == jt) {
          continue;
        }
        sum += -this->_matrix.get(it, jt) * _approximation[jt];
      }
      sum /= this->_matrix.get(it, it);
      new_approximation[it] = sum;
      this->_deviation[it] =
          std::abs(new_approximation[it] - this->_approximation[it]) /
          std::abs(new_approximation[it]);
    }
    _approximation = new_approximation;
    is_ready = true;
    for (const auto &it : this->_deviation) {
      if (it > _precision) {
        is_ready = false;
      }
    }
  } while (!is_ready);

  std::cout << "Results:" << std::endl;
  for (auto it : _approximation) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

bool Solver::make_diagonal_dominant() {
  auto &matrix_data = this->_matrix._data;
  auto &values = this->_values;

  int n = matrix_data.size();
  bool is_swapped;
  for (int i = 0; i < n; ++i) {
    is_swapped = false;
    double sum = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        sum += std::abs(matrix_data[i][j]);
      }
    }
    if (std::abs(matrix_data[i][i]) < sum) {
      for (int k = i + 1; k < n; ++k) {
        double k_sum = 0;
        for (int j = 0; j < n; ++j) {
          if (k != j) {
            k_sum += std::abs(matrix_data[k][j]);
          }
        }
        if (std::abs(matrix_data[k][k]) > k_sum) {
          std::swap(matrix_data[i], matrix_data[k]);
          std::swap(values[i], values[k]);
          is_swapped = true;
          break;
        }
      }
      if (!is_swapped) {
        return false;
      }
    }
  }
  return true;
}
