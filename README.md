# projectile-motion-sim

Projectile motion with quadratic air drag: derivation, numerical scheme,
and a C++ simulation of it.

- `projectile-motion.tex` / `projectile-motion.pdf` — the write-up. Derives
  the physical model, the Euler integration scheme, the stopping-condition
  analysis, and the architecture the simulation follows (Section 5).
- `include/`, `src/` — the simulation itself, built to that architecture.

## Status

**Phase 1**: physics core (`State`, `acceleration`, `step`,
`simulate_trajectory`) plus two validations, no graphics, no sweeps yet.

## Building and running

Requires CMake, a C++17 compiler, raylib, and OpenMP (all available via
GCC on Fedora).

```sh
./run.sh
```

or manually:

```sh
cmake -S . -B build
cmake --build build
./build/projectile-motion-sim
```

Phase 1 prints the results of two validations to stdout:

- **(a)** As the dimensionless drag strength `beta -> 0`, the optimal
  launch angle should approach 45 degrees.
- **(b)** Refining the time step `dt -> dt/2 -> dt/4` should show the
  range converging, with the change between successive refinements
  roughly halving each time (first-order convergence, since Euler's
  method is first order).

## Structure

- `include/projectile/` — the physics core. Header-only, pure functions,
  no dependency on raylib or iostream. Layered per the write-up: state ->
  acceleration -> step -> trajectory.
- `include/projectile.hpp` — umbrella header pulling in the whole core.
- `src/main.cpp` — Phase 1 entry point (validations only, for now).
