#pragma once
#include <random>
#include <vector>

class Simulation {
public:
  Simulation(int n_particles, double step_length,
             unsigned seed = 42); // Constructor

  void step();
  double meanSquaredDisplacement() const;

private:
  int n_;
  double step_length_;
  unsigned seed_;
  std::vector<double> x_, y_;
  std::mt19937 gen_;
};