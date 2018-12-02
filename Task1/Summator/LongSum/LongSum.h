//
// Created by user on 27.11.18.
//

#ifndef SUMMATOR_LONGSUM_H
#define SUMMATOR_LONGSUM_H

#include <glob.h>
#include <string>

#define MAX_LENGTH 100000
#define MOD 100

class LongSum {

    int sum[MAX_LENGTH];

public:
    LongSum();
    void Add(int* number, size_t length);
    int *getSum();
    std::string toString();
    void show();
};


#endif //SUMMATOR_LONGSUM_H
