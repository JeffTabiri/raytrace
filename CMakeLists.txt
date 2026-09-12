cmake_minimum_required(VERSION 4.0)
project(raytrace)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(raytrace ${SRC_FILES})

target_include_directories(raytrace PRIVATE include)



