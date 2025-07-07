cmake_minimum_required(VERSION 3.16)
project(MyGLFWApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your include directory for glad and KHR
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add GLFW include path manually (update if you're on Intel)
include_directories(/opt/homebrew/include)

# Source files
set(SOURCES
    src/main.cpp
    src/glad.c
)

# Add the executable
add_executable(MyGLFWApp ${SOURCES})

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