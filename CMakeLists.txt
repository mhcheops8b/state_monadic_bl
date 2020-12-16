# CMakeList.txt : CMake project for modal_state_bl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(state_monadic_bl)
# Add source to this project's executable.
add_executable (state_monadic_bl "state_monadic_bl.cpp")
target_include_directories(state_monadic_bl PRIVATE include)
#include_directories(include)
# TODO: Add tests and install targets if needed.
