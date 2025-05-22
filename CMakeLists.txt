cmake_minimum_required(VERSION 3.20)
project(DA1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Try to find OR-Tools system-wide ===
find_path(ORTOOLS_INCLUDE_DIR ortools/linear_solver/linear_solver.h)
find_library(ORTOOLS_LIBRARY ortools)

if(NOT ORTOOLS_INCLUDE_DIR OR NOT ORTOOLS_LIBRARY)
    message(FATAL_ERROR "Could not find OR-Tools. Please install it system-wide.")
endif()

# === Source files ===
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

# === Header files (for IDEs/navigation only) ===
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

# === Executable ===
add_executable(deliveryTruck ${SOURCES} ${HEADERS})

# === Include paths ===
target_include_directories(deliveryTruck PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Code
        ${ORTOOLS_INCLUDE_DIR}
)

# === Link OR-Tools ===
target_link_libraries(deliveryTruck ${ORTOOLS_LIBRARY})

# === Runtime linking path for macOS/Linux ===
if(APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path")
elseif(UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# === Dataset copy ===
file(COPY "Code/datasets" DESTINATION "${CMAKE_BINARY_DIR}")