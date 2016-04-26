cmake_minimum_required(VERSION 3.0)
project(rhf CXX)

find_package(Armadillo)
if (ARMADILLO_FOUND)
  include_directories("${ARMADILLO_INCLUDE_DIRS}")
endif (ARMADILLO_FOUND)

add_library(molecule 
  diag.cpp 
  utils.hpp 
  utils.cpp 
  molecule.hpp 
  molecule.cpp
  )

set(STUB "h2o_dzp")

add_custom_command(
  OUTPUT 
  "${STUB}_enuc.dat"
  "${STUB}_s.dat"
  "${STUB}_t.dat"
  "${STUB}_v.dat"
  "${STUB}_eri.dat"
  COMMAND "${CMAKE_COMMAND}" -E copy "${rhf_SOURCE_DIR}/${STUB}_enuc.dat" "${rhf_BINARY_DIR}/${STUB}_enuc.dat"
  COMMAND "${CMAKE_COMMAND}" -E copy "${rhf_SOURCE_DIR}/${STUB}_s.dat" "${rhf_BINARY_DIR}/${STUB}_s.dat"
  COMMAND "${CMAKE_COMMAND}" -E copy "${rhf_SOURCE_DIR}/${STUB}_t.dat" "${rhf_BINARY_DIR}/${STUB}_t.dat"
  COMMAND "${CMAKE_COMMAND}" -E copy "${rhf_SOURCE_DIR}/${STUB}_v.dat" "${rhf_BINARY_DIR}/${STUB}_v.dat"
  COMMAND "${CMAKE_COMMAND}" -E copy "${rhf_SOURCE_DIR}/${STUB}_eri.dat" "${rhf_BINARY_DIR}/${STUB}_eri.dat"
  DEPENDS
  "${rhf_SOURCE_DIR}/${STUB}_enuc.dat"
  "${rhf_SOURCE_DIR}/${STUB}_s.dat"
  "${rhf_SOURCE_DIR}/${STUB}_t.dat"
  "${rhf_SOURCE_DIR}/${STUB}_v.dat"
  "${rhf_SOURCE_DIR}/${STUB}_eri.dat"
  )

add_custom_target(inputs_${STUB} 
  DEPENDS 
  "${rhf_BINARY_DIR}/${STUB}_enuc.dat"
  "${rhf_BINARY_DIR}/${STUB}_s.dat"
  "${rhf_BINARY_DIR}/${STUB}_t.dat"
  "${rhf_BINARY_DIR}/${STUB}_v.dat"
  "${rhf_BINARY_DIR}/${STUB}_eri.dat"
  )

if (ARMADILLO_FOUND)
  add_executable(rhf_serial rhf_serial.cpp)
  add_dependencies(rhf_serial inputs_${STUB})
  target_link_libraries(rhf_serial molecule "${ARMADILLO_LIBRARIES}")
  add_executable(rhf_omp rhf_omp.cpp)
  add_dependencies(rhf_omp inputs_${STUB})
  target_link_libraries(rhf_omp molecule "${ARMADILLO_LIBRARIES}")
endif (ARMADILLO_FOUND)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # should check for Clang >= 3.7 here
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp=libomp")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  message(SEND_ERROR "Unrecognized CXX compiler: ${CXX_COMPILER_NAME}")
endif()
