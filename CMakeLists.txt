cmake_minimum_required(VERSION 3.16)
project(MyGLFWApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCES
    src/glad.c
    src/shaders.cpp
    src/glfwWindowCreation.cpp
    src/main.cpp
)

# Add the executable
add_executable(MyGLFWApp ${SOURCES})

# change to target include for lsp to pickup via cmake
target_include_directories(MyGLFWApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/GLFW
    ${CMAKE_SOURCE_DIR}/include/KHR
    /opt/homebrew/include
)

# Link GLFW
find_package(glfw3 REQUIRED)

target_link_libraries(MyGLFWApp PRIVATE glfw)

# macOS-specific system frameworks
if(APPLE)
    target_link_libraries(MyGLFWApp PRIVATE
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
