cmake_minimum_required(VERSION 3.12)
project(CLionOpenGL)

#include_directories("./include")
set(CMAKE_CXX_STANDARD 14)

#ADD_SUBDIRECTORY(src)

AUX_SOURCE_DIRECTORY("src" src_files)

add_executable(CLionOpenGL ${src_files})

#add_executable(CLionOpenGL "src/OpenGL01.cpp")

target_link_libraries(CLionOpenGL opengl32 glu32 freeglut)