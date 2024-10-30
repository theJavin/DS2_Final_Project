# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)
project(CartPoleRL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set Torch DIR and include paths
if(NOT DEFINED TORCH_ROOT)
    set(TORCH_ROOT "$ENV{HOME}/libtorch")
endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${TORCH_ROOT}")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Box2D REQUIRED)

# Find Torch with all required components
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

message(STATUS "TORCH_LIBRARIES: ${TORCH_LIBRARIES}")
message(STATUS "TORCH_INCLUDE_DIRS: ${TORCH_INCLUDE_DIRS}")

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

# Link libraries (order matters)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${TORCH_LIBRARIES}
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
    ${BOX2D_LIBRARIES}
)

# Set RPATH for Linux
if(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "${TORCH_ROOT}/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endif()

# Verify LibTorch version and components
execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo "Found LibTorch: ${TORCH_LIBRARIES}"
    COMMAND ${CMAKE_COMMAND} -E echo "LibTorch include dirs: ${TORCH_INCLUDE_DIRS}"
)

# Add definition to enable CUDA if available
if(TORCH_CUDA_AVAILABLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE TORCH_CUDA_AVAILABLE)
endif()