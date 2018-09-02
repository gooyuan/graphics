cmake_minimum_required(VERSION 3.12)
project(CLionOpenGL)

set(CMAKE_CXX_STANDARD 14)

#include_directories("include")
ADD_SUBDIRECTORY(src/c_pure)

ADD_SUBDIRECTORY(src/opengl)

#AUX_SOURCE_DIRECTORY("." src_files)

#add_executable(gldemo ${src_files})

# add_executable(CLionOpenGL "src/OpenGL01.cpp")
# add_executable(CLionOpenGL "src/OpenGL_Draw_Practice.cpp")

#target_link_libraries(gldemo opengl32 glu32 freeglut)