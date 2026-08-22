#pragma once

#include "constants.hpp"

namespace projectile {

// k = C/m (Section 5.1). Mass never appears on its own in the dynamics,
// only in this combination, so k is the single drag parameter the physics
// core works with. Units: 1/m.
struct DragParameter {
    double value;
};

// beta = k * v0^2 / g, the dimensionless ratio of drag to gravity
// (Section 5.1). This converts the dimensionless beta, which is the
// natural parameter for interpreting results, into the k that the
// dynamics actually use.
DragParameter drag_parameter_from_beta(double beta, double launch_speed) {
    return DragParameter{beta * GRAVITATIONAL_ACCELERATION / (launch_speed * launch_speed)};
}

} // namespace projectile
