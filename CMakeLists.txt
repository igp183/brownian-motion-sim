cmake_minimum_required(VERSION 3.10.0)
project(projectile-motion-sim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(projectile-motion-sim src/main.cpp)

target_include_directories(projectile-motion-sim PRIVATE include)

target_link_libraries(projectile-motion-sim PRIVATE
    raylib
    OpenMP::OpenMP_CXX
)
