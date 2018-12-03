cmake_minimum_required(VERSION 2.8.12.2)
project(MatrixMultiply)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(MatrixMultiply1 main.cpp MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h)
add_executable(GraphDrawer TimeElapser/TimeElapser.cpp MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h
        MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h)

target_link_libraries (GraphDrawer ${CMAKE_THREAD_LIBS_INIT} pthread)