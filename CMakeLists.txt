cmake_minimum_required(VERSION 3.12)
project(CLionOpenGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CLionOpenGL OpenGL01.cpp)
target_link_libraries(CLionOpenGL opengl32 glu32 freeglut)