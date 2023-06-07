# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

project( cgalTest )


# Include cgal and boost headers



# # include gmp
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/gmp-6.2.1)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/CGAL-5.5.2/include)
# set(CGAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/CGAL-5.5.2/include)





# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/boost_1_81_0)
# set(BOOST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/boost_1_81_0)

# # include libigl
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)
# set(LIBIGL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)
# set(LIBIGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/libigl-2.4.0/include)

# include_directories(${LIBIGL_DIR})

SET( EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/eigen-3.3.9)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
include_directories(${EIGEN3_INCLUDE_DIR})

SET(GMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/gmp-6.2.1)
IF( NOT GMP_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable GMP_INCLUDE_DIR to the include directory of your GMP installation.")
ENDIF()
include_directories(${GMP_INCLUDE_DIR})

add_executable(app app.cpp)

# find_library(GMP_LIBRARY PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libraries/gmp-6.2.1)

find_library(GMP_LIBRARIES gmp PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
find_library(GMPXX_LIBRARIES gmpxx PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
find_library(MPFR_LIBRARIES mpfr PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
# target_link_libraries(app ${EIGEN3_LIBRARIES} ${GMP_LIBRARIES})
target_link_libraries(app gmp mpfr)

add_definitions(-w)

