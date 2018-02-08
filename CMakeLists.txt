cmake_minimum_required(VERSION 3.0)
project(mysql_cpp)

set(CMAKE_CXX_STANDARD 11)
include_directories(
        include
        src/include)

aux_source_directory(src SRC)

add_library(mysql_cpp STATIC
        ${SRC})

target_include_directories(mysql_cpp PUBLIC include)