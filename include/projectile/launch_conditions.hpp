#pragma once

#include "angle.hpp"
#include "constants.hpp"
#include "drag_parameter.hpp"
#include "state.hpp"
#include "time_step.hpp"

#include <cmath>

namespace projectile {

// Everything needed to launch a projectile, bundled together so it
// travels through the higher layers (trajectory, sweeps) as one value
// instead of three easily-swapped doubles.
struct LaunchConditions {
    double launch_speed;
    Angle launch_angle;
    DragParameter drag;
};

State initial_state(const LaunchConditions& launch) {
    return State{
        0.0,
        0.0,
        launch.launch_speed * std::cos(launch.launch_angle.radians),
        launch.launch_speed * std::sin(launch.launch_angle.radians),
    };
}

// tau ~= 2 v0 sin(theta) / g, the flight time in the drag-free case
// (Section 3), used only to size dt.
double estimate_drag_free_flight_time(const LaunchConditions& launch) {
    return 2.0 * launch.launch_speed * std::sin(launch.launch_angle.radians)
        / GRAVITATIONAL_ACCELERATION;
}

// Derives dt per trajectory from tau and the dt/tau <= 1e-3 criterion
// (Section 5.3), so every launch angle gets a comparable number of steps.
TimeStep derive_time_step(const LaunchConditions& launch) {
    return TimeStep{estimate_drag_free_flight_time(launch) * MAX_TIME_STEP_TO_FLIGHT_TIME_RATIO};
}

} // namespace projectile
