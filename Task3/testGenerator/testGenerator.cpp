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

    void generate(const char* filename, int count_n, int count_k) {


        std::ofstream myfile;
        myfile.open (filename);

        myfile << count_n << " " << count_k << std::endl;

        for (int i = 0; i < count_n; i++) {
            for (int j = 0; j < count_k; j++) {
                double num = (double)rand() / RAND_MAX + rand();
                myfile << num;
            }
            myfile << std::endl;
            myfile.flush();
        }
        myfile.close();
    }
}