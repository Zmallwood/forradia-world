#include "Rect_F.h"

namespace FW
{
    bool Rect_F::Contains(Point_F point) const
    {
        return point.x >= x && point.y >= y &&
            point.x < x + w && point.y < y + h;
    }
}
