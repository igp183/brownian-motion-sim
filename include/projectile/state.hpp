#pragma once

#include "constants.hpp"

#include <cmath>

namespace projectile {

// The full state of the projectile at one instant: position and velocity.
// Named members instead of a bare double[4] so a call site can never mix
// up which slot is which.
struct State {
    double x;
    double y;
    double vx;
    double vy;
};

double speed(const State& state) {
    return std::sqrt(state.vx * state.vx + state.vy * state.vy);
}

bool is_below_ground(const State& state) {
    return state.y <= GROUND_HEIGHT;
}

} // namespace projectile
