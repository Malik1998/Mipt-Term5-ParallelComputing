//
// Created by user on 27.11.18.
//

#include <string>
#include <fstream>
#include <ctime>
#include "math.h"
#include "../../LongSum/LongSum.h"
#pragma once
namespace testGenerator {

    std::string generate(const char* filename, size_t count = 1000, size_t maxLength = 10) {


        std::ofstream myfile;
        myfile.open (filename);
        LongSum longSum;
        for (size_t i = 0; i < count; i++) {
          //  std::srand(unsigned(std::time(0)));
            size_t random_size = std::rand() % maxLength + 1;
            int *newInt = new int[random_size];
            std::fill(newInt, newInt + random_size, 0);
            for (size_t j = 0; j < random_size; j++) {
                int num = std::rand() % MOD;
                newInt[j] = num;
                if (num < 10) {
                    myfile << 0;
                }
                myfile << num;
            }
            myfile << std::endl;
            myfile.flush();
            longSum.Add(newInt, random_size);
            delete[] newInt;
        }
        myfile.close();
        return longSum.toString();
    }
}