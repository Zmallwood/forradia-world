#include "rect_f.hpp"

namespace fw {
  bool
  rect_f::contains(
      point_f point) const {
    return point.x >= x &&
           point.y >= y &&
           point.x < x + w &&
           point.y < y + h;
  }
}
