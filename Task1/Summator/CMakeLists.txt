cmake_minimum_required(VERSION 3.12)
project(Summator)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

add_executable(Summator main.cpp LongSum/LongSum.cpp LongSum/LongSum.h Summator/Summator.cpp Summator/Summator.h
        ReadFullFile/FullFileReader.cpp ReadFullFile/FullFileReader.h)

target_link_libraries (Summator ${CMAKE_THREAD_LIBS_INIT})