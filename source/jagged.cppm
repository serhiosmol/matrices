module;

#include <cstdlib>

export module jagged;

namespace matrices {

export template <typename T>
class JaggedArrayMatrix {
public:
    explicit JaggedArrayMatrix(std::size_t size) : size_(size) {}

    std::size_t size() const { return size_; }
private:
    std::size_t size_;
};

} // namespace matrices