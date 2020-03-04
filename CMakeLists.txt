cmake_minimum_required(VERSION 2.8.0)
project(OpenServer)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif ()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(include /opt/inc)

add_executable(OpenServer main.cpp)

add_library(eorl SHARED IMPORTED)
set_property(TARGET eorl PROPERTY IMPORTED_LOCATION /opt/lib/libeORL.so)

target_link_libraries(OpenServer eorl m pthread)
