cmake_minimum_required(VERSION 2.8)
project(Xarajlt_Project)

if(NOT CMAKE_BUILD_TYPE)
     set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(app_xarajlt.exe source/main.cpp source/xarajlt.cpp source/state.cpp source/move.cpp)
target_link_libraries(app_xarajlt.exe)
