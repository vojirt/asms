cmake_minimum_required(VERSION 2.8)

project(tracker)
  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -pedantic -Wno-long-long")
endif()

FIND_PACKAGE( OpenCV REQUIRED )
link_directories ( ${OpenCV_LIB_DIR} )
MESSAGE(STATUS "OpenCV_LIB_DIR: ${OpenCV_LIB_DIR}")

include_directories ( ${OpenCV_INCLUDE_DIRS} )
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_subdirectory(src)

add_executable(asms_vot main_vot.cpp)
target_link_libraries(asms_vot ${OpenCV_LIBS} color)

add_executable(asms_demo main_demo.cpp )
target_link_libraries(asms_demo ${OpenCV_LIBS} color )

# Try to find TraX header and library ...
FIND_FILE(TRAX_HEADER NAMES trax.h)
IF (EXISTS ${TRAX_HEADER})
    GET_FILENAME_COMPONENT(TRAX_DIR ${TRAX_HEADER} DIRECTORY)
    LINK_DIRECTORIES(${TRAX_DIR}) # Add library directory
    INCLUDE_DIRECTORIES(${TRAX_DIR}) # Add includes directory

    add_executable(asms_trax main_trax.cpp)
    target_link_libraries(asms_trax ${OpenCV_LIBS} color trax trax_opencv)
ENDIF()

