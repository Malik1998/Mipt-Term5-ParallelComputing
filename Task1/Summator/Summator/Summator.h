//
// Created by user on 27.11.18.
//

#ifndef SUMMATOR_SUMMATOR_H
#define SUMMATOR_SUMMATOR_H


#include <cstddef>
#include <zconf.h>
#include "../LongSum/LongSum.h"

class Summator {

    struct Bounds {
        Summator* summator = nullptr;
        LongSum* longSum = nullptr;
        int* new_number = nullptr;
        int left;
        int right;

        Bounds(int left_, int right_, Summator* summator_) : left(left_), right(right_), summator(summator_) {}


    };

private:
    int count_of_threads;
    char *text;
    int count_of_lines;
    int max_length;
    LongSum longSum;

public:
    Summator(const char* filename, int count_of_threads_, int& error);

    int calculate();

    LongSum getSum();
    void getSumString(std::string& a);

    ~Summator();

private:
    static void *calculatePart(void *params);

    static void make_number(int *pInt, char *string, int i, int r);

    int getNextBound(int PreviosEnd, int threadIndex);
};


#endif //SUMMATOR_SUMMATOR_H
