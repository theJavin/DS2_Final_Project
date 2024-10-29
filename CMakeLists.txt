
# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)
project(CartPoleRL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Box2D REQUIRED)
find_package(LibTorch REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${BOX2D_INCLUDE_DIRS}
    ${TORCH_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/main.cpp
    src/CartPoleSimulation.cpp
    src/PhysicsSystem.cpp
    src/Renderer.cpp
    src/RLTrainer.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
    Box2D
    ${TORCH_LIBRARIES}
)

# cmake/FindLibTorch.cmake
set(TORCH_ROOT "" CACHE PATH "Path to LibTorch installation")

find_path(TORCH_INCLUDE_DIRS torch/torch.h
    PATHS
    ${TORCH_ROOT}/include
    ${TORCH_ROOT}/include/torch/csrc/api/include
)

if(WIN32)
    find_library(TORCH_LIBRARIES torch
        PATHS
        ${TORCH_ROOT}/lib
    )
else()
    find_library(TORCH_LIBRARIES torch
        PATHS
        ${TORCH_ROOT}/lib
    )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibTorch DEFAULT_MSG
    TORCH_LIBRARIES
    TORCH_INCLUDE_DIRS
)

mark_as_advanced(TORCH_INCLUDE_DIRS TORCH_LIBRARIES)
