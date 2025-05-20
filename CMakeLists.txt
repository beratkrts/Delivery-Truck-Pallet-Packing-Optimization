cmake_minimum_required(VERSION 3.30)
project(DA1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Define source files
set(SOURCES
    Code/main.cpp
    Code/algorithms/greedy.cpp
    Code/cli/menu.cpp
    Code/input/data_loader.cpp
)

# Define header files
set(HEADERS
    Code/algorithms/common.h
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

# Set output directory
set_target_properties(deliveryTruck PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Copy dataset files to build directory
file(COPY "Code/datasets" DESTINATION "${CMAKE_BINARY_DIR}")