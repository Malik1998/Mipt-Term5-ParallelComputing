//
// Created by user on 27.11.18.
//

#ifndef SUMMATOR_LONGSUM_H
#define SUMMATOR_LONGSUM_H

#include <glob.h>

#define MAX_LENGTH 10
#define MOD 100

class LongSum {

    int sum[MAX_LENGTH];

public:
    LongSum();
    void Add(int* number, size_t length);
    int *getSum();

    void show();
};


#endif //SUMMATOR_LONGSUM_H
