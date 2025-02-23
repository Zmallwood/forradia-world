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

  point_f rect_f::get_center() const {
    return {x + w/2.0f, y + h/2.0f};
  }
}
