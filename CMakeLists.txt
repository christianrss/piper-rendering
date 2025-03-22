cmake_minimum_required(VERSION 3.12)

project(PiperRendering)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_executable(PiperRendering main.cpp screen.cpp)

target_link_libraries(PiperRendering ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})