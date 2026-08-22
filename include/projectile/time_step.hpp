#pragma once

namespace projectile {

// Delta t, the duration of one Euler step. Wrapped so it can never be
// passed where a plain duration or coefficient was expected instead.
struct TimeStep {
    double seconds;
};

TimeStep half(TimeStep dt) {
    return TimeStep{dt.seconds / 2.0};
}

} // namespace projectile
