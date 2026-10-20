module;

#include <cmath>
#include <cstddef>
#include <ranges>
#include <utility>

export module jagged;

import array;

namespace matrices {

export template <typename T>
class JaggedArrayMatrix final {
public:
  explicit JaggedArrayMatrix(std::size_t size) : size_(size), rows_(size) {
    for (auto i : std::views::iota(0uz, size)) {
      rows_[i] = Array<T>(size);
    }
  }

  T& operator()(std::size_t i, std::size_t j) { return rows_[i][j]; }

  const T& operator()(std::size_t i, std::size_t j) const { return rows_[i][j]; }

  std::size_t size() const { return size_; }

private:
  std::size_t size_;
  Array<Array<T>> rows_;
};

export template <typename T>
T determinant(JaggedArrayMatrix<T>& a) {
  auto n = a.size();
  if (!n) {
    return T{0};
  }

  T sign = T{1};

  for (std::size_t k : std::views::iota(0uz, n)) {
    std::size_t k_prime = k;
    T p = T{0};
    for (std::size_t i : std::views::iota(k, n)) {
      if (std::abs(a(i, k)) > p) {
        p = a(i, k);
        k_prime = i;
      }
    }

    if (p == T{0}) {
      return T{0};
    }

    if (k != k_prime) {
      for (std::size_t i : std::views::iota(0uz, n)) {
        std::swap(a(k, i), a(k_prime, i));
      }
      sign = -sign;
    }

    for (std::size_t i : std::views::iota(k + 1, n)) {
      a(i, k) = a(i, k) / a(k, k);
      for (std::size_t j : std::views::iota(k + 1, n)) {
        a(i, j) -= a(i, k) * a(k, j);
      }
    }
  }

  T d = sign;
  for (std::size_t k : std::views::iota(0uz, n)) {
    d *= a(k, k);
  }
  return d;
}

}  // namespace matrices
