project(MyProject)
cmake_minimum_required(VERSION 3.16)

if(NOT POLICY CMP0070 AND POLICY CMP0053)
  # Only set CMP0053 to OLD with CMake<3.10, otherwise there is a warning.
  cmake_policy(SET CMP0053 OLD)
endif()

if(POLICY CMP0071)
  cmake_policy(SET CMP0071 NEW)
endif()

if(POLICY CMP0011)
  cmake_policy(SET CMP0011 NEW)
endif()

find_package(CGAL REQUIRED COMPONENTS Qt5)
if(CGAL_Qt5_FOUND)
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

add_executable(
  MyExec
  My_linear_cell_complex_incremental_builder.h
  elementVille.cpp
  immeuble.cpp
  test.cpp)

target_link_libraries(MyExec PUBLIC CGAL::CGAL CGAL::CGAL_Qt5)
