#pragma once

namespace projectile {

constexpr double GRAVITATIONAL_ACCELERATION = 9.81; // m/s^2

constexpr double PI = 3.14159265358979323846;

constexpr double GROUND_HEIGHT = 0.0; // m

// See Section 3 of the write-up: the criterion is dt/tau <= 1e-3.
constexpr double MAX_TIME_STEP_TO_FLIGHT_TIME_RATIO = 1.0e-3;

// Mandatory cap on simulation steps (Section 4): the velocity stopping
// test may never fire for strong drag, so the loop must have a hard limit.
constexpr int DEFAULT_MAX_STEPS = 200'000;

} // namespace projectile
