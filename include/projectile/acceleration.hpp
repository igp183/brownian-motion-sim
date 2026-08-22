#pragma once

#include "constants.hpp"
#include "drag_parameter.hpp"
#include "state.hpp"

namespace projectile {

// The acceleration produced by gravity and quadratic drag (Eq. accel_k).
struct Acceleration {
    double x;
    double y;
};

double horizontal_drag_acceleration(const State& state, DragParameter k) {
    return -k.value * speed(state) * state.vx;
}

double vertical_acceleration(const State& state, DragParameter k) {
    return -GRAVITATIONAL_ACCELERATION - k.value * speed(state) * state.vy;
}

// Acceleration layer (Section 5.2): given a state and k, return (ax, ay).
Acceleration acceleration(const State& state, DragParameter k) {
    return Acceleration{
        horizontal_drag_acceleration(state, k),
        vertical_acceleration(state, k),
    };
}

} // namespace projectile
