cmake_minimum_required(VERSION 2.6)
project(fracc)

add_executable(fracc
  fracc.cpp
  program.cpp
  fn.cpp
  simplefn.cpp
  exp.cpp
  seqfn.cpp
  call.cpp
  slot.cpp
  whilefn.cpp
  iffn.cpp
)
target_link_libraries(fracc yaml-cpp)
