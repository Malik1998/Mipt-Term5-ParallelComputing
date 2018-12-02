cmake_minimum_required(VERSION 3.12)
project(Summator)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

add_executable(Summator main.cpp LongSum/LongSum.cpp LongSum/LongSum.h Summator/Summator.cpp Summator/Summator.h
        ReadFullFile/FullFileReader.cpp ReadFullFile/FullFileReader.h tests/testGenerator/testGenerator.cpp tests/TimeElapser/TimeElapser.cpp)

include_directories(
        External testLib/googletest-master/googletest/googlemock/gtest
)

add_executable(SummatorTest tests/SummatorTest/SummatorTest.cpp tests/SummatorTest/SummatorTest.h LongSum/LongSum.cpp LongSum/LongSum.h Summator/Summator.cpp Summator/Summator.h
        ReadFullFile/FullFileReader.cpp ReadFullFile/FullFileReader.h)


add_executable(GraphTimeElapser tests/TimeElapser/TimeElapser.cpp LongSum/LongSum.cpp LongSum/LongSum.h Summator/Summator.cpp Summator/Summator.h
        ReadFullFile/FullFileReader.cpp ReadFullFile/FullFileReader.h)

target_link_libraries (GraphTimeElapser ${CMAKE_THREAD_LIBS_INIT} gtest gtest_main pthread)

target_link_libraries (SummatorTest ${CMAKE_THREAD_LIBS_INIT} gtest gtest_main pthread)