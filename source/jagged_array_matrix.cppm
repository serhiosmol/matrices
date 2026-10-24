module;

#include <cmath>
#include <cstddef>
#include <iostream>
#include <optional>
#include <print>
#include <ranges>
#include <utility>

export module jagged_array_matrix;

import jagged_array;

namespace matrices {

export template <typename T>
class JaggedArrayMatrix final {
public:
  explicit JaggedArrayMatrix(std::size_t rows, std::size_t cols, T val = T{}) :
    array_(rows, cols, val) {}

  template <typename It>
  explicit JaggedArrayMatrix(std::size_t rows, std::size_t cols, It start, It finish) :
    array_(rows, cols, start, finish) {}

  static JaggedArrayMatrix eye(std::size_t n) {}

  T& operator[](std::size_t i, std::size_t j) { return array_[i, j]; }
  const T& operator[](std::size_t i, std::size_t j) const { return array_[i, j]; }

  std::size_t rows() const { return array_.rows(); }
  std::size_t cols() const { return array_.cols(); }

  void dump(std::ostream& os = std::cout) {
    for (std::size_t i : std::views::iota(0uz, rows())) {
      for (std::size_t j : std::views::iota(0uz, cols())) {
        std::print("{:8.3f}", array_[i, j]);
      }
      std::println();
    }
  }

  std::optional<T> trace() const {
    std::size_t rows = array_.rows();
    std::size_t cols = array_.cols();
    if (rows != cols) {
      return std::nullopt;
    }

    auto n = rows;
    T trace = T{0};

    for (std::size_t i : std::views::iota(0uz, rows)) {
      trace += array_[i, i];
    }

    return trace;
  }

  std::optional<T> determinant() {
    auto rows = array_.rows();
    auto cols = array_.cols();
    if (rows != cols) {
      return std::nullopt;
    }

    auto n = rows;
    if (!n) {
      return T{1};
    }

    T sign = T{1};
    JaggedArrayMatrix<T> a = *this;

    for (std::size_t k : std::views::iota(0uz, n)) {
      std::size_t k_prime = k;
      T p = T{0};
      for (std::size_t i : std::views::iota(k, n)) {
        if (std::abs(a[i, k]) > p) {
          p = a[i, k];
          k_prime = i;
        }
      }

      if (p == T{0}) {
        return T{0};
      }

      if (k != k_prime) {
        for (std::size_t i : std::views::iota(0uz, n)) {
          std::swap(a[k, i], a[k_prime, i]);
        }
        sign = -sign;
      }

      for (std::size_t i : std::views::iota(k + 1, n)) {
        a[i, k] = a[i, k] / a[k, k];
        for (std::size_t j : std::views::iota(k + 1, n)) {
          a[i, j] -= a[i, k] * a[k, j];
        }
      }
    }

    T d = sign;
    for (std::size_t k : std::views::iota(0uz, n)) {
      d *= a[k, k];
    }

    return d;
  }

private:
  array::JaggedArray<T> array_;
};

}  // namespace matrices
