cmake_minimum_required(VERSION 4.0)
project(PhysicsSandbox VERSION 0.1.0 LANGUAGES C CXX)

find_package(sdl3 REQUIRED CONFIG)

add_executable(PhysicsSandbox src/main.cpp)

set_property(TARGET PhysicsSandbox PROPERTY CXX_STANDARD 17)

target_link_libraries(PhysicsSandbox PRIVATE SDL3::SDL3)