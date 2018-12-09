//
// Created by user on 27.11.18.
//

#include "Summator.h"
#include "../ReadFullFile/FullFileReader.h"
#include <pthread.h>
#include <iostream>
#include <cstring>

Summator::Summator(const char *filename, int count_of_threads_, int &error) : count_of_lines(0),
        max_length(2), count_of_threads(count_of_threads_) {

    if(FullFileReader::readFullFile(filename, &text)) {
        error = 1;
        return ;
    }

    int cur_length = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            count_of_lines++;
            if (cur_length > max_length) {
                max_length = cur_length;
            }
            cur_length = 0;
        } else {
            cur_length++;
        }
    }
    max_length = max_length / 2 + max_length % 2 + count_of_lines;
    longSum = LongSum(max_length, error);
    if (error) {
        return;
    }

}

int Summator::calculate() {

    pthread_t *ThreadPool;
    if(!(ThreadPool = (pthread_t *) malloc(count_of_threads * sizeof(pthread_t)))) {
        std::cerr << "Allocation error";
        return 5;
    }
    Bounds *bounds;
    if(!(bounds =(Bounds *) malloc(count_of_threads * sizeof(Bounds)))) {
        std::cerr << "Allocation error";
        return 5;
    }

    LongSum **longsums;
    if(!(longsums =(LongSum **) malloc(count_of_threads * sizeof(LongSum*)))) {
        std::cerr << "Allocation error";
        return 5;
    }

    int **new_numbers;
    if(!(new_numbers =(int**) malloc(count_of_threads * sizeof(int*)))) {
        std::cerr << "Allocation error";
        return 5;
    }

    int previos_end = 0;

    for (int i = 0; i < count_of_threads; i++) {
        int nextBound = getNextBound(previos_end, i);

        bounds[i] = Bounds(previos_end + 1, nextBound, this);

        int error;

        if(!(longsums[i] =(LongSum*) malloc(sizeof(LongSum)))) {
            std::cerr << "Allocation error";
            return 5;
        }

        (*longsums[i]) = LongSum(max_length, error);

        if (error) {
            return error;
        }

        bounds[i].longSum = longsums[i];

        if(!(new_numbers[i] =(int*) malloc(max_length * sizeof(int)))) {
            std::cerr << "Allocation error";
            return 5;
        }

        memset(new_numbers[i], 0, max_length * sizeof(int));

        bounds[i].new_number = new_numbers[i];

        previos_end = nextBound;

        if (i == 0) {
            bounds[i].left = 0;
        }

        if (pthread_create(&ThreadPool[i], NULL, this->calculatePart, &bounds[i])) {
            std::cerr << "Error creating";
            return 2;
        }
    }

    for (int i = 0; i < count_of_threads; i++) {
        if (pthread_join(ThreadPool[i], NULL)) {
            std::cerr << "Error joining";
            return 3;
        }

        longSum.Add(bounds[i].longSum->getSum(), max_length);
        free(new_numbers[i]);
    }

    free(bounds);

    free(longsums);

    free(new_numbers);

    free(ThreadPool);

    return 0;
}

void *Summator::calculatePart(void *params) {
    Bounds *bounds = static_cast<Bounds*>(params);

    int max_length = bounds->summator->max_length;

    int* new_number = bounds->new_number;

    LongSum *longSum = (bounds->longSum);

    int size_of_number = 0;
    int previos_start = bounds->right - 1;
    for (int i = bounds->right - 1; i >= bounds->left; i--) {
        if (bounds->summator->text[i] == '\n') {
            int size_of_array = size_of_number / 2 + size_of_number % 2;
            if (size_of_array != 0) {
                make_number(new_number + max_length - size_of_array - 1, bounds->summator->text + previos_start, size_of_number, size_of_array);
                longSum->Add(new_number + max_length - size_of_array - 1, size_of_array);
            }
            size_of_number = 0;
            previos_start = i - 1;
        } else {
            size_of_number++;
        }
        if (i == bounds->left) {
            break;
        }
    }

    int size_of_array = size_of_number / 2 + size_of_number % 2;
    if (size_of_array != 0) {

        make_number(new_number + max_length - size_of_array - 1, bounds->summator->text + previos_start, size_of_number, size_of_array);
        longSum->Add(new_number + max_length - size_of_array - 1, size_of_array);
    }

}

LongSum Summator::getSum() {
    return longSum;
}

void Summator::getSumString(std::string& a) {
    longSum.toString(a);
}

void Summator::make_number(int *pInt, char *string, int length, int sizeArray) {

    pInt[sizeArray - 1] = string[0] - '0';
    if (length == 1) {
        return;
    }
    bool firstFull = false;
    for (int i = 1, k = sizeArray - 1; i < length; i++) {
        int num = (*(string - i)) - '0';
        if (firstFull) {
            pInt[k] = num;
            firstFull = false;
        } else {
            firstFull = true;
            pInt[k] = num * 10 + pInt[k];
            k--;
        }
        if (k >= sizeArray) {
            return;
        }
    }
}

int Summator::getNextBound(int previosEnd, int threadIndex) {
    int i = previosEnd;
    if (threadIndex == count_of_threads - 1) {
        for (;text[i] != '\0'; i++) {}
        i--;
        if (text[i] != '\n') {
            i++;
        }
    } else {
        int countToPart = count_of_lines / count_of_threads;
        i++;
        for (; countToPart != 0; i++) {
            if (text[i] == '\n') {
                countToPart--;
            }
        }
        i--;
    }

    return i;
}

Summator::~Summator() {

}

