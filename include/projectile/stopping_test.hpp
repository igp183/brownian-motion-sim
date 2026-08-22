#pragma once

#include "constants.hpp"
#include "state.hpp"

#include <optional>

namespace projectile {

// The outcome of one stopping test on one trajectory: the step at which
// it fired and the interpolated range at that crossing, or nothing if it
// never fired before the step limit.
struct StoppingTestOutcome {
    std::optional<int> step_index;
    std::optional<double> range;
};

bool has_fired(const StoppingTestOutcome& outcome) {
    return outcome.step_index.has_value();
}

// Where, between value_before and value_after, does a linear interpolant
// cross threshold? Returns a fraction in [0, 1] (Section 4: "interpolate
// the final step").
double interpolation_fraction(double value_before, double value_after, double threshold) {
    return (threshold - value_before) / (value_after - value_before);
}

double lerp(double start, double end, double fraction) {
    return start + fraction * (end - start);
}

// Height test (Eq. stop_y): the projectile has landed once y <= 0. Only
// ever evaluated on the state *after* a step is taken, so the y = 0
// launch state itself is never mistaken for a landing.
bool has_crossed_ground(const State& current) {
    return is_below_ground(current);
}

StoppingTestOutcome make_height_test_outcome(const State& previous, const State& current, int step_index) {
    const double crossing_fraction = interpolation_fraction(previous.y, current.y, GROUND_HEIGHT);
    const double range = lerp(previous.x, current.x, crossing_fraction);
    return StoppingTestOutcome{step_index, range};
}

// Velocity test (Eq. stop_vy): the drag-free landing condition
// vy <= -v0y, applied to the drag case too.
bool has_crossed_velocity_threshold(const State& current, double initial_vertical_speed) {
    return current.vy <= -initial_vertical_speed;
}

StoppingTestOutcome make_velocity_test_outcome(
    const State& previous,
    const State& current,
    double initial_vertical_speed,
    int step_index
) {
    const double crossing_fraction =
        interpolation_fraction(previous.vy, current.vy, -initial_vertical_speed);
    const double range = lerp(previous.x, current.x, crossing_fraction);
    return StoppingTestOutcome{step_index, range};
}

} // namespace projectile
