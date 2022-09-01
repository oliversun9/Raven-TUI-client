cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 20)

project(Raven LANGUAGES CXX)

add_executable(raven main.cpp)

add_subdirectory(life-cycle)
add_subdirectory(text-ui)
add_subdirectory(util)

target_link_libraries(raven PUBLIC LifeCycle)
target_link_libraries(raven PUBLIC TextUI)
target_link_libraries(raven PUBLIC UTIL)

find_package(Threads REQUIRED)
target_link_libraries(raven PRIVATE Threads::Threads)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(raven PUBLIC ${CURSES_LIBRARIES})