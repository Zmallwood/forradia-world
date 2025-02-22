#include "RectF.hpp"

namespace FW
{
    bool RectF::Contains(PointF point) const
    {
        return point.x >= x && point.y >= y &&
            point.x < x + w && point.y < y + h;
    }
}
