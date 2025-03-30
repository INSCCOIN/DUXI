cmake_minimum_required(VERSION 3.10)
project(DUXI)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
set(SOURCES
    main.cpp
    Renderer.cpp
    Window.cpp
    Shader.cpp
    Mesh.cpp
    Camera.cpp
)

# Find and include GLFW
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})
link_directories(${GLFW3_LIBRARY_DIRS})

# Find and include GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
set(GLEW_LIBRARY /usr/local/lib/libGLEW.dylib)

# Find and include GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Add the executable
add_executable(DUXI ${SOURCES})

# Link the libraries
target_link_libraries(DUXI ${GLFW3_LIBRARIES} ${GLEW_LIBRARY} ${GLM_LIBRARIES} ${CMAKE_DL_LIBS} glfw "-framework OpenGL")