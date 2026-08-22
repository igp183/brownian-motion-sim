#pragma once

#include "constants.hpp"

namespace projectile {

// An angle, stored internally in radians. Use the named constructors
// below instead of building one by hand, so the unit is never ambiguous
// at the call site.
struct Angle {
    double radians;
};

Angle angle_from_degrees(double degrees) {
    return Angle{degrees * PI / 180.0};
}

Angle angle_from_radians(double radians) {
    return Angle{radians};
}

double to_degrees(Angle angle) {
    return angle.radians * 180.0 / PI;
}

} // namespace projectile
