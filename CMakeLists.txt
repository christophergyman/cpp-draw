cmake_minimum_required(VERSION 3.16)
project(MyGLFWApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ImGui source files (with backends subdirectory)
set(IMGUI_SOURCES
    include/imgui/imgui.cpp
    include/imgui/imgui_demo.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
    include/imgui/backends/imgui_impl_glfw.cpp
    include/imgui/backends/imgui_impl_opengl3.cpp
)

# Your existing source files
set(SOURCES
    src/glad.c
    src/shaders.cpp
    src/glfwWindowCreation.cpp
    src/main.cpp
)

# Combine all sources
set(ALL_SOURCES ${SOURCES} ${IMGUI_SOURCES})

# Add the executable
add_executable(MyGLFWApp ${ALL_SOURCES})

# Include directories
target_include_directories(MyGLFWApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/GLFW
    ${CMAKE_SOURCE_DIR}/include/KHR
    ${CMAKE_SOURCE_DIR}/include/imgui
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
