#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")"

if [ ! -f build/CMakeCache.txt ]; then
  cmake -S . -B build
fi

cmake --build build

exec ./build/projectile-motion-sim
