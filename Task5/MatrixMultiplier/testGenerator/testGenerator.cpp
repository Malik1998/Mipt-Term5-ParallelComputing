//
// Created by user on 27.11.18.
//

#include <string>
#include <fstream>
#include <ctime>
#include "math.h"
#include <iostream>
#include <cstdlib>
#include "mpi.h"
#include "../MatrixMultiplier2/MatrixMultiplier2.h"

#pragma once

namespace testGenerator {


    void generate(const char* filename, int count_n, int count_k) throw() {


        std::ofstream myfile;
        myfile.open (filename);

        myfile.write(reinterpret_cast<char*>(&count_n), sizeof(int));
        myfile.write(reinterpret_cast<char*>(&count_k), sizeof(int));

        for (size_t i = 0; i < count_n; i++) {
            for (size_t j = 0; j < count_k; j++) {
                double num = (double)rand() / RAND_MAX + rand();
                myfile.write(reinterpret_cast<char*>(&num), sizeof(double));
            }
        }
        myfile.close();
    }
    void mult(char *filenameA, char *filenameB, double **pDouble) throw() {


        MatrixMultiplier2 *matrixMultiplier = new MatrixMultiplier2(filenameA, filenameB, 1,
                                                                    const_cast<char *>("c.txt"));
        matrixMultiplier->multiply();
        matrixMultiplier->writeTo(pDouble);
        delete matrixMultiplier;

    }


    void gener(char* filenameA, char* filenameB, int count_n, int count_k, int count_m, double **answ) throw() {
        generate(filenameA, count_n, count_k);
        generate(filenameB, count_k, count_m);
        mult(filenameA, filenameB, answ);
    }

}