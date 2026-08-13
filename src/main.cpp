#include "simulation.hpp"
#include <iostream>

const int n_particles = 10000;
const double step_length = 1.0;
const int n_steps = 1000;

int main() {
    const int n_particles = 10000;
    const double step_length = 1.0;
    const int n_steps = 1000;

    Simulation sim(n_particles, step_length);

    for (int t = 1; t <= n_steps; ++t) {
        sim.step();

        if (t % 100 == 0) {
            double msd = sim.meanSquaredDisplacement();
            std::cout << "t=" << t << "  MSD=" << msd
                      << "  MSD/t=" << msd / t << "\n";
        }
    }

    return 0;
}