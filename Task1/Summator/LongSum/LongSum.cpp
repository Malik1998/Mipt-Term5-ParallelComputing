//
// Created by user on 27.11.18.
//

#include <iostream>
#include <cstring>
#include "LongSum.h"

void LongSum::Add(int *number, int length) {

    int ost = 0;
    int k = static_cast<int>(length - 1);
    if (max_length == 0) {
        return;
    }
    for (int i = max_length - 1; i >= 0; i--, k--) {
        sum[i] += ost;
        if (k >= 0) {
            sum[i] += number[k];
        }

        ost = (sum[i]) / MOD;
        sum[i] %= MOD;

        if (k < 0 && ost == 0) { // Methods of Optimizations
            break;
        }

        if (i == 0) {
            break;
        }
    }
}

int *LongSum::getSum() {
    return sum;
}

void LongSum::show() {
    bool isFirst = true;
    bool isNumber = false;
    for (int i = 0; i < max_length; i++) {
        if (sum[i] != 0) {
            isNumber = true;
        }
        if (isNumber) {
            if (sum[i] < 10) {
                if (!isFirst) {
                    std::cout << "0";
                }
            }

            std::cout << sum[i];

            isFirst = false;
        }
    }
    std::cout << std::endl;
}

LongSum::LongSum(int max_length_, int &error):max_length(max_length_), sum(nullptr) {
    if(!(sum = (int *) malloc(max_length * sizeof(int)))) {
        std::cerr << "Bad alloc" << std::endl;
        sum = nullptr;
        error = 1;
        max_length = 0;
        return ;
    }
    error = 0;
    memset(sum, 0, max_length * sizeof(int));
}

int LongSum::toString(std::string &result) {

    bool isFirst = true;
    bool isNumber = false;
    for (int i = 0; i < max_length; i++) {
        if (sum[i] != 0) {
            isNumber = true;
        }
        if (isNumber) {
            if (sum[i] < 10) {
                if (!isFirst) {
                    result += "0";
                }
            }

            result += std::to_string(sum[i]);

            isFirst = false;
        }
    }
    return 0;
}

LongSum::~LongSum() {
    if (max_length > 0 && sum != nullptr) {
        free(sum);
        max_length = 0;
        sum = nullptr;
    }
}

LongSum::LongSum(): max_length(0) {
    sum = nullptr;
}

LongSum &LongSum::operator=(const LongSum &longSum_) {
    if( !(this->sum = (int*)malloc(longSum_.max_length * sizeof(int)))) {
        this->max_length = 0;
        this->sum = nullptr;
        return *this;
    }
    this->max_length = longSum_.max_length;
    std::memcpy(this->sum, longSum_.sum, static_cast<size_t>(longSum_.max_length) * sizeof(int));
    return *this;
}

LongSum::LongSum(const LongSum &longSum_) {
    (*this) = longSum_;

}
