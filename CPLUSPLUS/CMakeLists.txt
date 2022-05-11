cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

project(Raven LANGUAGES CXX)

add_executable(raven main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(raven PRIVATE Threads::Threads)