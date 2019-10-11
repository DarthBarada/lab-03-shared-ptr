cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab03)

add_executable(main main.cpp)

target_include_directories(
main
PUBLIC
../include
)
