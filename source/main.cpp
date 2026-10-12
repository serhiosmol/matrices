#include <print>
#include <cstdlib>

import jagged;

int main() {
    matrices::JaggedArrayMatrix<int> matrix(5);
    std::size_t matrix_size = matrix.size();
    std::println("{}", matrix_size);
    return 0;
}