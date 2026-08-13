cmake_minimum_required(VERSION 3.10.0)
project(brownian-motion-sim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(brownian-motion-sim src/main.cpp)

target_link_libraries(brownian-motion-sim PRIVATE
    raylib
    OpenMP::OpenMP_CXX
)