//
// Created by user on 27.11.18.
//

#include "Summator.h"
#include "../ReadFullFile/FullFileReader.h"
#include <pthread.h>
#include <iostream>

Summator::Summator(const char *filename, size_t count_of_threads_) : count_of_threads(count_of_threads_) {
    FullFileReader::readFullFile(filename, &text);
    count_of_lines = 0;
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            count_of_lines++;
        }
    }
}

int Summator::calculate() {

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        std::cerr << "mutex init failed";
        return 1;
    }

    pthread_t *ThreadPool = new pthread_t[count_of_threads];
    int ** newNumbers = new int*[count_of_threads];
    LongSum** pLongSum = new LongSum*[count_of_threads];
    Bounds** bounds = new Bounds*[count_of_threads];

    size_t previos_end = 0;

    for (size_t i = 0; i < count_of_threads; i++) {
        size_t nextBound = getNextBound(previos_end, i);
        bounds[i] = new Bounds(previos_end + 1, nextBound, this);
        newNumbers[i] = new int[MAX_LENGTH];
        pLongSum[i] = new LongSum();

        bounds[i]->newNumber = newNumbers[i];
        bounds[i]->longSum = pLongSum[i];

        previos_end = nextBound;

        if (i == 0) {
            bounds[i]->left = 0;
        }

        if (pthread_create(&ThreadPool[i], NULL, this->calculatePart, bounds[i])) {
            std::cerr << "Error creating";
            return 2;
        }
    }

    for (size_t i = 0; i < count_of_threads; i++) {
        if (pthread_join(ThreadPool[i], NULL)) {
            std::cerr << "Error joining";
            return 3;
        }
        delete bounds[i];
        delete newNumbers[i];
        delete pLongSum[i];
    }

    delete[] bounds;
    delete[] newNumbers;
    delete[] pLongSum;
    delete[] ThreadPool;

    return 0;
}

void *Summator::calculatePart(void *params) {
    Bounds *bounds = static_cast<Bounds*>(params);
    LongSum *longSum = bounds->longSum;
    int *new_number = bounds->newNumber;

   // std::cout << bounds->left << " " << bounds->right << std::endl;
  //s  std::cout << bounds->summator->text[bounds->left] << " to " << bounds->summator->text[bounds->right] << std::endl;
    size_t size_of_number = 0;
    size_t previos_start = bounds->right - 1;
    for (size_t i = bounds->right - 1; i >= bounds->left; i--) {
        if (bounds->summator->text[i] == '\n') {
            size_t size_of_array = size_of_number / 2 + size_of_number % 2;
            if (size_of_array != 0) {
                make_number(new_number + MAX_LENGTH - size_of_array - 1, bounds->summator->text + previos_start, size_of_number, size_of_array);
                longSum->Add(new_number + MAX_LENGTH - size_of_array - 1, size_of_array);
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

    size_t size_of_array = size_of_number / 2 + size_of_number % 2;
    if (size_of_array != 0) {

        make_number(new_number + MAX_LENGTH - size_of_array - 1, bounds->summator->text + previos_start, size_of_number, size_of_array);
        longSum->Add(new_number + MAX_LENGTH - size_of_array - 1, size_of_array);
    }

    pthread_mutex_lock(&bounds->summator->lock);

    bounds->summator->longSum.Add(longSum->getSum(), MAX_LENGTH);

    pthread_mutex_unlock(&bounds->summator->lock);
}

LongSum Summator::getSum() {
    return longSum;
}

void Summator::make_number(int *pInt, char *string, size_t length, size_t sizeArray) {

    pInt[sizeArray - 1] = string[0] - '0';
    if (length == 1) {
        return;
    }
    bool firstFull = false;
    for (size_t i = 1, k = sizeArray - 1; i < length; i++) {
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

size_t Summator::getNextBound(size_t previosEnd, size_t threadIndex) {
    size_t i = previosEnd;
    if (threadIndex == count_of_threads - 1) {
        for (;text[i] != '\0'; i++) {}
        i--;
        if (text[i] != '\n') {
            i++;
        }
    } else {
        size_t countToPart = count_of_lines / count_of_threads;
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

