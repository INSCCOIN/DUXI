cmake_minimum_required(VERSION 3.10)
project(GameEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Add executable
add_executable(GameEngine ${SOURCES})

# Include directories
include_directories(src)

# Link libraries (e.g., OpenGL, GLFW, GLEW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add GLEW library
find_library(GLEW_LIB GLEW REQUIRED)

target_link_libraries(GameEngine OpenGL::GL glfw ${GLEW_LIB})