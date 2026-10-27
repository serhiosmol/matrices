module;

#include <cmath>
#include <limits>

export module floating_point_comparing;

namespace cmp {

export template <typename FloatT, typename SizeT>
bool are_equal(FloatT a, FloatT b, FloatT max_elem, SizeT size) {
  FloatT diff = std::fabs(a - b);

  if (diff <= max_elem * std::numeric_limits<FloatT>::epsilon() * static_cast<FloatT>(size)) {
    return true;
  }
  return false;
}

}  // namespace cmp