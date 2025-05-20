cmake_minimum_required(VERSION 3.20)
project(DA1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
set(SOURCES
    Code/main.cpp
    Code/algorithms/greedy.cpp
    Code/algorithms/brute_force.cpp
    Code/algorithms/dp.cpp
    Code/algorithms/ilp_solver.cpp
    Code/algorithms/backtracking.cpp
    Code/cli/menu.cpp
    Code/input/data_loader.cpp
)

# Define header files
set(HEADERS
    Code/algorithms/common.h
    Code/algorithms/greedy.h
    Code/algorithms/brute_force.h
    Code/algorithms/dp.h
    Code/algorithms/ilp_solver.h
    Code/algorithms/backtracking.h
    Code/cli/menu.h
    Code/input/data_loader.h
    Code/utils/timer.h
)

# Create executable
add_executable(deliveryTruck ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(deliveryTruck PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Copy dataset files to build directory
file(COPY "Code/datasets" DESTINATION "${CMAKE_BINARY_DIR}")