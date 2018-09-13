cmake_minimum_required(VERSION 3.12)
project(CLionOpenGL)

set(CMAKE_CXX_STANDARD 14)

# include_directories("include")
#ADD_SUBDIRECTORY(src)

AUX_SOURCE_DIRECTORY("." src_files)

add_executable(cpp_demo ${src_files})