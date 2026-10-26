module;

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <utility>

export module array;

namespace array {

export template <typename T>
class Array final {
public:
  Array(std::size_t size, T val = T{}) : size_(size), ptr_(size > 0 ? new T[size]{} : nullptr) {
    for (std::size_t i : std::views::iota(0uz, size_)) {
      ptr_[i] = val;
    }
  }

  template <typename It>
  Array(std::size_t size, It start, It finish) :
    size_(size), ptr_(size > 0 ? new T[size]{} : nullptr) {
    for (std::size_t i = 0; i < size && start != finish; i++) {
      ptr_[i] = *start;
      start++;
    }
  }

  ~Array() { delete[] ptr_; }

  Array(const Array& rhs) : size_(rhs.size_), ptr_(rhs.size_ > 0 ? new T[size_] : nullptr) {
    std::copy(rhs.ptr_, rhs.ptr_ + size_, ptr_);
  }

  Array(Array&& rhs) noexcept : size_(rhs.size_), ptr_(rhs.ptr_) {
    rhs.size_ = 0;
    rhs.ptr_ = nullptr;
  }

  Array& operator=(const Array& rhs) {
    if (this == &rhs) {
      return *this;
    }

    size_ = rhs.size_;
    delete[] ptr_;
    ptr_ = new T[size_];
    std::copy(rhs.ptr_, rhs.ptr_ + size_, ptr_);
    return *this;
  }

  Array& operator=(Array&& rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    std::swap(ptr_, rhs.ptr_);
    std::swap(size_, rhs.size_);
    return *this;
  }

  std::size_t size() const { return size_; }

  T& operator[](std::size_t i) { return ptr_[i]; }

  const T& operator[](std::size_t i) const { return ptr_[i]; }

private:
  std::size_t size_;
  T* ptr_;
};

}  // namespace array