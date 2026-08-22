// Phase 1: physics core validation.
//
// Runs the two checks from Section 5.6 of the write-up before anything
// else gets built on top of the core:
//   (a) as beta -> 0, the optimal launch angle should approach 45 deg.
//   (b) refining dt -> dt/2 -> dt/4 should show first-order convergence,
//       i.e. the change between successive refinements should roughly
//       halve each time.

#include "projectile.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace projectile;

namespace {

constexpr double VALIDATION_LAUNCH_SPEED = 20.0; // m/s

constexpr double ANGLE_SEARCH_MIN_DEGREES = 1.0;
constexpr double ANGLE_SEARCH_MAX_DEGREES = 89.0;
constexpr double ANGLE_SEARCH_STEP_DEGREES = 0.1;

// The height test always fires (gravity eventually wins), so it is the
// one used as "the range" here; the velocity test is exercised inside
// simulate_trajectory but is not needed for these two validations.
double range_at_angle(double launch_speed, double angle_degrees,
                      DragParameter drag) {
  const LaunchConditions launch{launch_speed, angle_from_degrees(angle_degrees),
                                drag};
  const TimeStep dt = derive_time_step(launch);
  const TrajectoryOutcome outcome = simulate_trajectory(launch, dt);
  return outcome.height_test.range.value_or(0.0);
}

double find_optimal_angle_degrees(double launch_speed, DragParameter drag) {
  double best_angle_degrees = ANGLE_SEARCH_MIN_DEGREES;
  double best_range = range_at_angle(launch_speed, best_angle_degrees, drag);

  for (double angle_degrees = ANGLE_SEARCH_MIN_DEGREES;
       angle_degrees <= ANGLE_SEARCH_MAX_DEGREES;
       angle_degrees += ANGLE_SEARCH_STEP_DEGREES) {
    const double range = range_at_angle(launch_speed, angle_degrees, drag);
    if (range > best_range) {
      best_range = range;
      best_angle_degrees = angle_degrees;
    }
  }

  return best_angle_degrees;
}

void validate_low_drag_limit_recovers_45_degrees() {
  std::cout << "=== Validation (a): beta -> 0 should give optimal angle -> 45 "
               "deg ===\n";

  const std::vector<double> beta_values = {1.0, 0.1, 0.01, 0.001, 0.0001};

  for (double beta : beta_values) {
    const DragParameter drag =
        drag_parameter_from_beta(beta, VALIDATION_LAUNCH_SPEED);
    const double optimal_angle_degrees =
        find_optimal_angle_degrees(VALIDATION_LAUNCH_SPEED, drag);

    std::cout << "  beta = " << std::setw(10) << std::defaultfloat << beta
              << "   optimal angle = " << std::fixed << std::setprecision(2)
              << optimal_angle_degrees << " deg\n";
  }
  std::cout << '\n';
}

constexpr double CONVERGENCE_TEST_BETA = 0.5;
constexpr double CONVERGENCE_TEST_ANGLE_DEGREES = 45.0;

void validate_first_order_convergence() {
  std::cout << "=== Validation (b): refining dt should show first-order "
               "convergence ===\n";

  const DragParameter drag =
      drag_parameter_from_beta(CONVERGENCE_TEST_BETA, VALIDATION_LAUNCH_SPEED);
  const LaunchConditions launch{
      VALIDATION_LAUNCH_SPEED,
      angle_from_degrees(CONVERGENCE_TEST_ANGLE_DEGREES),
      drag,
  };

  const TimeStep coarse_dt = derive_time_step(launch);
  const TimeStep medium_dt = half(coarse_dt);
  const TimeStep fine_dt = half(medium_dt);

  const double range_coarse =
      simulate_trajectory(launch, coarse_dt).height_test.range.value_or(0.0);
  const double range_medium =
      simulate_trajectory(launch, medium_dt).height_test.range.value_or(0.0);
  const double range_fine =
      simulate_trajectory(launch, fine_dt).height_test.range.value_or(0.0);

  const double first_refinement_change = std::abs(range_medium - range_coarse);
  const double second_refinement_change = std::abs(range_fine - range_medium);
  const double halving_ratio =
      first_refinement_change / second_refinement_change;

  std::cout << std::fixed << std::setprecision(6);
  std::cout << "  range(dt)     = " << range_coarse << " m\n";
  std::cout << "  range(dt/2)   = " << range_medium << " m\n";
  std::cout << "  range(dt/4)   = " << range_fine << " m\n";
  std::cout << "  |change 1->2| = " << first_refinement_change << " m\n";
  std::cout << "  |change 2->3| = " << second_refinement_change << " m\n";
  std::cout << "  ratio (expect ~2 for first-order convergence) = "
            << halving_ratio << '\n';
}

} // namespace

int main() {
  validate_low_drag_limit_recovers_45_degrees();
  validate_first_order_convergence();
  return 0;
}
