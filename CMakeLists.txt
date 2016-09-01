cmake_minimum_required(VERSION 2.8)

project(tracker)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -Wno-long-long")
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

add_executable(demo main_demo.cpp )
target_link_libraries(demo ${OpenCV_LIBS} color )
