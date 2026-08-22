#pragma once

#include "acceleration.hpp"
#include "drag_parameter.hpp"
#include "state.hpp"
#include "time_step.hpp"

namespace projectile {

double next_x(const State& state, TimeStep dt) {
    return state.x + state.vx * dt.seconds;
}

double next_y(const State& state, TimeStep dt) {
    return state.y + state.vy * dt.seconds;
}

double next_vx(const State& state, Acceleration a, TimeStep dt) {
    return state.vx + a.x * dt.seconds;
}

double next_vy(const State& state, Acceleration a, TimeStep dt) {
    return state.vy + a.y * dt.seconds;
}

// Step layer (Section 5.2): given a state, dt and k, return the state one
// step later. Position is advanced using the velocity at the *start* of
// the step, matching the explicit Euler scheme derived in Section 3.
State step(const State& state, TimeStep dt, DragParameter k) {
    const Acceleration a = acceleration(state, k);
    return State{
        next_x(state, dt),
        next_y(state, dt),
        next_vx(state, a, dt),
        next_vy(state, a, dt),
    };
}

} // namespace projectile
