#pragma once

#include "constants.hpp"
#include "launch_conditions.hpp"
#include "state.hpp"
#include "step.hpp"
#include "stopping_test.hpp"
#include "time_step.hpp"

#include <optional>

namespace projectile {

// Both stopping tests, run on the one trajectory (Section 5.5): the
// stopping test never affects the dynamics, only when we stop reading,
// so a single pass can record when each would have fired.
struct TrajectoryOutcome {
    StoppingTestOutcome velocity_test;
    StoppingTestOutcome height_test;
    bool step_limit_reached;
};

enum class StoppingTestKind {
    Velocity,
    Height,
};

bool both_tests_have_fired(const TrajectoryOutcome& outcome) {
    return has_fired(outcome.velocity_test) && has_fired(outcome.height_test);
}

// Which test's condition was met at the smaller step index, if either
// fired at all.
std::optional<StoppingTestKind> first_test_to_fire(const TrajectoryOutcome& outcome) {
    const bool velocity_fired = has_fired(outcome.velocity_test);
    const bool height_fired = has_fired(outcome.height_test);

    if (!velocity_fired && !height_fired) {
        return std::nullopt;
    }
    if (!velocity_fired) {
        return StoppingTestKind::Height;
    }
    if (!height_fired) {
        return StoppingTestKind::Velocity;
    }
    return (outcome.velocity_test.step_index.value() <= outcome.height_test.step_index.value())
        ? StoppingTestKind::Velocity
        : StoppingTestKind::Height;
}

// Trajectory layer (Section 5.2): given launch conditions, step until
// both stopping tests have fired (or the step limit is hit — mandatory,
// since the velocity test may never fire for C > 0, Section 4), and
// report both. No trajectory points are stored; only the running state
// is kept, so a sweep over many trajectories allocates nothing.
TrajectoryOutcome simulate_trajectory(
    const LaunchConditions& launch,
    TimeStep dt,
    int max_steps = DEFAULT_MAX_STEPS
) {
    State previous = initial_state(launch);
    const double initial_vertical_speed = previous.vy;

    TrajectoryOutcome outcome{};

    for (int step_index = 0; step_index < max_steps; ++step_index) {
        const State current = step(previous, dt, launch.drag);

        if (!has_fired(outcome.height_test) && has_crossed_ground(current)) {
            outcome.height_test = make_height_test_outcome(previous, current, step_index);
        }

        if (!has_fired(outcome.velocity_test)
            && has_crossed_velocity_threshold(current, initial_vertical_speed)) {
            outcome.velocity_test =
                make_velocity_test_outcome(previous, current, initial_vertical_speed, step_index);
        }

        if (both_tests_have_fired(outcome)) {
            return outcome;
        }

        previous = current;
    }

    outcome.step_limit_reached = true;
    return outcome;
}

} // namespace projectile
