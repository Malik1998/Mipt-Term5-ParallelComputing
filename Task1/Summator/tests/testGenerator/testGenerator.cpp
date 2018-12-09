//
// Created by user on 27.11.18.
//

#include <string>
#include <fstream>
#include <ctime>
#include "math.h"
#include <cstdlib>
#include "../../LongSum/LongSum.h"
#pragma once
namespace testGenerator {

    std::string generate(const char* filename, int count = 1000, int maxLength = 10) {


        std::ofstream myfile;
        myfile.open (filename);
        int error;
        LongSum longSum(maxLength + count, error);

        if (error) {
            return "Error";
        }

        bool alloc_error = false;

        for (int i = 0; i < count; i++) {
          //  std::srand(unsigned(std::time(0)));
            int random_size = std::rand() % maxLength + 1;
            int *newInt;
            if (! ( newInt = (int*) malloc(maxLength * sizeof(int)))) {
                alloc_error = true;
                break;
            }
            std::fill(newInt, newInt + random_size, 0);
            for (int j = 0; j < random_size; j++) {
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
            free(newInt);
        }
        myfile.close();
        std::string result;
        if (longSum.toString(result) != 0 || alloc_error) {
            result = "Error";
        }
        return result;
    }
}