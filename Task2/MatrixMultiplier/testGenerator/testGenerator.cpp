//
// Created by user on 27.11.18.
//

#include <string>
#include <fstream>
#include <ctime>
#include "math.h"
#include <cstdlib>

#pragma once

namespace testGenerator {

    void generate(const char* filename, size_t count_n, size_t count_k) {


        std::ofstream myfile;
        myfile.open (filename);

        myfile << count_n << " " << count_k << std::endl;

        for (size_t i = 0; i < count_n; i++) {
            for (size_t j = 0; j < count_k; j++) {
                double num = (double)rand() / RAND_MAX + rand();
                myfile << num;
            }
            myfile << std::endl;
            myfile.flush();
        }
        myfile.close();
    }
}