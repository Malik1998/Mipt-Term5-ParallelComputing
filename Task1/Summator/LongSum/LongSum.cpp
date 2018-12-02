//
// Created by user on 27.11.18.
//

#include <iostream>
#include "LongSum.h"

void LongSum::Add(int *number, size_t length) {

    int ost = 0;
    int k = static_cast<int>(length - 1);
    for (size_t i = MAX_LENGTH - 1; i >= 0; i--, k--) {
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
    for (size_t i = 0; i < MAX_LENGTH; i++) {
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
}

LongSum::LongSum() {
    for(int i = 0; i < MAX_LENGTH; i++) {
        sum[i] = 0;
    }

}

std::string LongSum::toString() {
    std::string result;
    bool isFirst = true;
    bool isNumber = false;
    for (size_t i = 0; i < MAX_LENGTH; i++) {
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
    return result;
}
