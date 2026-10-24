#include <cstddef>
#include <iostream>
#include <print>
#include <string>
#include <optional>
#include <vector>

import jagged_array_matrix;
import util;

int main() {
  auto result = util::read_value<std::size_t>();
  if (!result) {
    return 1;
  }

  auto n = result.value();
  // auto expected_count = n * n;

  std::vector<double> v{1, 0, 0, 0, 1, 0, 0, 0, 1};

  matrices::JaggedArrayMatrix<double> matrix(n, n, v.begin(), v.end());

#if 0
  std::size_t element_count = 0;
  for (std::size_t i = 0; i < n; i++) {
    for (std::size_t j = 0; j < n; j++) {
      auto value = util::read_value<double>();
      if (!value) {
        std::println(stderr, "error: expected {} elements for a {}x{} matrix, got {}.",
                     expected_count, n, n, element_count);
        return 1;
      }
      matrix[i, j] = value.value();
      element_count++;
    }
  }

  std::cin >> std::ws;
  if (std::cin.peek() != std::char_traits<char>::eof()) {
    std::println(stderr, "error: too many arguments, first {} were expected", expected_count);
    return 1;
  }
#endif
  // std::println("{}", matrices::determinant<double>(matrix));
  matrix.dump();
  auto t = matrix.trace();
  auto d = matrix.determinant();
  if (t.has_value() && d.has_value()) {
    std::println("trace: {}, determinant: {}", *t, *d);
  } else {
    std::println("error: not a square matrix");
  }

  return 0;
}
