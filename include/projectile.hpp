#pragma once

// Umbrella header for the physics core. Pulls in every layer described
// in Section 5.2 of the write-up, from the state representation up to
// full trajectories. Pure, header-only, and free of any dependency on
// raylib, iostream, or anything else — rendering and I/O may depend on
// this, never the reverse.

#include "projectile/acceleration.hpp"
#include "projectile/angle.hpp"
#include "projectile/constants.hpp"
#include "projectile/drag_parameter.hpp"
#include "projectile/launch_conditions.hpp"
#include "projectile/state.hpp"
#include "projectile/step.hpp"
#include "projectile/stopping_test.hpp"
#include "projectile/time_step.hpp"
#include "projectile/trajectory.hpp"
