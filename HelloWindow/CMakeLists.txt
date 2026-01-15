cmake_minimum_required(VERSION 3.16)

project(HelloWindow LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(glfw3 CONFIG REQUIRED)

# GLM
find_package(glm CONFIG REQUIRED)

# GLAD
add_library(glad
    glad.c
)

target_include_directories(glad PUBLIC
    include
)

# Executable
add_executable(HelloWindow
    main.cpp
)

target_link_libraries(HelloWindow
    PRIVATE
        glad
        glfw
        OpenGL::GL
        glm::glm
)
