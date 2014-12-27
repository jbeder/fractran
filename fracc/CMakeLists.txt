cmake_minimum_required(VERSION 2.6)
project(fracc)

add_executable(fracc
  call.cpp
  call.h
  exp.cpp
  exp.h
  fn.cpp
  fn.h
  fracc.cpp
  iffn.cpp
  iffn.h
  program.cpp
  program.h
  seqfn.cpp
  seqfn.h
  simplefn.cpp
  simplefn.h
  slot.cpp
  slot.h
  util.h
  whilefn.cpp
  whilefn.h
)
target_link_libraries(fracc yaml-cpp)
