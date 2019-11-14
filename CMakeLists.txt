cmake_minimum_required(VERSION 3.15)
project(std_future_thread_counter)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(std_future_thread_counter main.cpp)

target_link_libraries(std_future_thread_counter Threads::Threads)

