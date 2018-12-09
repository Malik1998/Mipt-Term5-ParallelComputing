cmake_minimum_required(VERSION 2.8.12.2)
project(MatrixMultiply)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(MatrixMultiply1 main.cpp MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h MatrixMultiplier2/MatrixMultiplier2.cpp MatrixMultiplier2/MatrixMultiplier2.h)
add_executable(GraphDrawer TimeElapser/TimeElapser.cpp MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h
        MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h MatrixMultiplier2/MatrixMultiplier2.cpp testGenerator/GenerateTest.cpp tests/tests.cpp)

add_executable(TimeElapser1 TimeElapser/TimeElapser.cpp
        MatrixMultiply/MatrixMultiplier.cpp MatrixMultiply/MatrixMultiplier.h MatrixMultiplier2/MatrixMultiplier2.cpp MatrixMultiplier2/MatrixMultiplier2.h)


add_executable(Gener testGenerator/GenerateTest.cpp
        MatrixMultiplier2/MatrixMultiplier2.cpp MatrixMultiplier2/MatrixMultiplier2.h)


target_link_libraries(Gener ${MPI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pthread)

target_link_libraries(TimeElapser1 ${MPI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pthread)

target_link_libraries(MatrixMultiply1 ${MPI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} pthread)

if(MPI_COMPILE_FLAGS)
    set_target_properties(MatrixMultiply1 PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(MatrixMultiply1 PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()


target_link_libraries (GraphDrawer ${CMAKE_THREAD_LIBS_INIT} pthread)