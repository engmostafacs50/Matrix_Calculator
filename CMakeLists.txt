cmake_minimum_required(VERSION 3.10)
project(MatricesCalculator)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(MatricesCalculator ${SRC_FILES} "include/LinearSystem.h" "src/LinearSystem/LinearSystem.cpp")
target_include_directories(MatricesCalculator PRIVATE include)
