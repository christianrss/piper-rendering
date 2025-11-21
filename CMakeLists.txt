cmake_minimum_required(VERSION 3.12)

project(PiperRendering)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad
    libs/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    libs/glad/include
)

include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    main.cpp
    screen.cpp
    input.cpp
    shader.cpp
    quad.cpp
)

target_link_libraries(${PROJECT_NAME}
    glad
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
)