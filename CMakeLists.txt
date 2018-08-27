cmake_minimum_required(VERSION 3.12)
project(CLionOpenGL)

include_directories("./include")
set(CMAKE_CXX_STANDARD 14)
aux_source_directory("./src/*.cpp" src_files)

add_executable(CLionOpenGL ${src_files})

target_link_libraries(CLionOpenGL opengl32 glu32 freeglut)