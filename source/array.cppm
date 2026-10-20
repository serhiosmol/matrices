module;

#include <cstddef>

export module array;

namespace matrices {

export template <typename T>
class Array final {
public:
  Array() noexcept = default;

  explicit Array(std::size_t size) : size_(size), data_(size ? new T[size]{} : nullptr) {}

  ~Array() { delete[] data_; }

  Array(const Array& rhs) : size_(rhs.size_), data_(rhs.size_ ? new T[rhs.size_]{} : nullptr) {
    for (std::size_t i = 0; i < rhs.size_; i++) {
      data_[i] = rhs.data_[i];
    }
  }

  Array& operator=(const Array& rhs) {
    if (this != &rhs) {
      Array tmp(rhs);
      swap(tmp);
    }
    return *this;
  }

  Array(Array&& rhs) noexcept : size_(rhs.size_), data_(rhs.data_) {
    rhs.size_ = 0;
    rhs.data_ = nullptr;
  }

  Array& operator=(Array&& rhs) noexcept {
    if (this != &rhs) {
      delete[] data_;
      data_ = rhs.data_;
      size_ = rhs.size_;
      rhs.data_ = nullptr;
      rhs.size_ = 0;
    }
    return *this;
  }

  void swap(Array& rhs) noexcept {
    std::size_t s = size_;
    size_ = rhs.size_;
    rhs.size_ = s;
    T* d = data_;
    data_ = rhs.data_;
    rhs.data_ = d;
  }

  std::size_t size() const noexcept { return size_; }

  T& operator[](std::size_t i) { return data_[i]; }

  const T& operator[](std::size_t i) const noexcept { return data_[i]; }

  T* data() noexcept { return data_; }

  const T* data() const noexcept { return data_; }

private:
  std::size_t size_ = 0;
  T* data_ = nullptr;
};

}  // namespace matrices