# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

project( cgalTest )


# Include cgal and boost headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/CGAL-5.5.2/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/boost_1_81_0)
# include libigl
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)
# # include gmp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/gmp-6.2.1)

set(CGAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/CGAL-5.5.2/include)
set(BOOST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/boost_1_81_0)

set(LIBIGL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)
set(LIBIGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)

include_directories(${LIBIGL_DIR})

add_executable(main main.cpp)

SET( EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/eigen-3.3.9)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
include_directories(${EIGEN3_INCLUDE_DIR})

SET(GMPXX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/gmp-6.2.1)
include_directories(${GMPXX_INCLUDE_DIR})

SET(MPFR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mpfr-4.2.0/src)
include_directories(${MPFR_INCLUDE_DIR})

# find_library(GMP_LIBRARIES gmp PATHS ${GMP_INCLUDE_DIR})
# find_library(GMPXX_LIBRARIES gmpxx PATHS ${GMP_INCLUDE_DIR})
# find_library(MPFR_LIBRARIES mpfr PATHS ${MPFR_INCLUDE_DIR})
# target_link_libraries(app ${EIGEN3_LIBRARIES} ${GMP_LIBRARIES})

# target_link_libraries(main gmp gmpxx mpfr)
target_link_libraries(main ${GMPXX_INCLUDE_DIR} ${MPFR_INCLUDE_DIR})
# include xatlas
# SET(xatlas ${CMAKE_CURRENT_SOURCE_DIR}/libraries/xatlas/source/xatlas)
# include_directories(${xatlas})
# target_link_libraries(main PRIVATE xatlas)

add_definitions(-w)

set_target_properties(main
PROPERTIES OUTPUT_NAME "index"
CFLAGS "-O3"
LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s DEMANGLE_SUPPORT=1 --bind"
)


