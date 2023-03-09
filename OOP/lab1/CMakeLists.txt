# CMakeList.txt : CMake project for lab1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("lab1")

# Add source to this project's executable.
add_executable (lab1 "lab1.c" "lab1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
