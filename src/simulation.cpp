#include "simulation.hpp"
#include <random>

Simulation::Simulation(int n_particles, double step_length, unsigned seed) {
  n_ = n_particles;
  step_length_ = step_length;
  seed_ = seed;
  x_ = std::vector<double>(n_particles, 0.0);
  y_ = std::vector<double>(n_particles, 0.0);
  gen_.seed(seed_);
}

void Simulation::step() {
  std::normal_distribution<double> dist(0.0, step_length_);

  for (int i = 0; i < n_; ++i) {
    x_[i] += dist(gen_);
    y_[i] += dist(gen_);
  }
}