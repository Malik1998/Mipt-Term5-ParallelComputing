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
        Summator* summator;
        int *newNumber;
        LongSum *longSum;
        size_t left;
        size_t right;

        Bounds(size_t left_, size_t right_, Summator* summator_) : left(left_), right(right_), summator(summator_) {}
    };

private:
    size_t count_of_threads;
    char *text;
    size_t count_of_lines;
    LongSum longSum;
    pthread_mutex_t lock;

public:
    Summator(const char* filename, size_t count_of_threads_);

    int calculate();

    LongSum getSum();

private:
    static void *calculatePart(void *params);

    static void make_number(int *pInt, char *string, size_t i, size_t r);

    size_t getNextBound(size_t PreviosEnd, size_t threadIndex);
};


#endif //SUMMATOR_SUMMATOR_H
