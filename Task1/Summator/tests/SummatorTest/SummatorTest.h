//
// Created by user on 08.09.18.
//

#ifndef PROCESSOR_PROCESSORTEST_H
#define PROCESSOR_PROCESSORTEST_H
#include <gtest/gtest.h>

class SummatorTest : public ::testing::Test {
public:
    SummatorTest() { /* init protected members here */ };
    ~SummatorTest() { /* free protected members here */ };
    void SetUp() { /* called before every test */ };
    void TearDown() { /* called after every test */ };
};


#endif //PROCESSOR_PROCESSORTEST_H
