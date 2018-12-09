//
// Created by user on 27.11.18.
//

#ifndef SUMMATOR_LONGSUM_H
#define SUMMATOR_LONGSUM_H

#include <glob.h>
#include <string>
#define MOD 100

class LongSum {

private:
    int *sum = nullptr;
    int max_length = 0;

public:
    explicit LongSum(int max_length_, int& error);
    LongSum();
    LongSum(const LongSum& longSum_);

    LongSum& operator=(const LongSum& longSum_);

    void Add(int* number, int length);
    int *getSum();
    int toString(std::string& result);
    void show();
    ~LongSum();
};


#endif //SUMMATOR_LONGSUM_H
