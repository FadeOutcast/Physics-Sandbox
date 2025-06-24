cmake_minimum_required(VERSION 4.0)
project(PhysicsSandbox VERSION 0.1.0 LANGUAGES C CXX)

find_package(sdl3 REQUIRED CONFIG)

include_directories(${CMAKE_SOURCE_DIR}/include)

# we define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# add_executable(PhysicsSandbox "${MY_SOURCES}")

add_executable(PhysicsSandbox 
                src/main.cpp
                src/MainLoop.cpp
                src/Shape.cpp)


set_property(TARGET PhysicsSandbox PROPERTY CXX_STANDARD 17)

target_link_libraries(PhysicsSandbox PRIVATE SDL3::SDL3)