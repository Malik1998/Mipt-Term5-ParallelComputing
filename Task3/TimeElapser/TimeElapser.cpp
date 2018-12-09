//
// Created by user on 02.12.18.
//

#include <fstream>
#include <time.h>
#include "../testGenerator/testGenerator.cpp"
#include "../MatrixMultiply/MatrixMultiplier.h"

int main(int argc, char **argv) {
   // testGenerator::generate("A.txt", 1000, 1000);
   // testGenerator::generate("B.txt", 1000, 1000);

    std::ofstream myfile;
    myfile.open(argv[1]);
    int max_threads = 10;

    myfile << "ns = np.array([";
    for(int i = 1; i < max_threads; i++) {
        myfile << i;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }
    myfile << "])\n";


    myfile << "time = np.array([";
    for (int i = 1; i < max_threads; i++) {
        int error;
        MatrixMultiplier matrixMultiplier("A.txt", "B.txt", i, error, "C.txt");

        struct timespec start, finish;
        double elapsed;

        clock_gettime(CLOCK_MONOTONIC, &start);

        matrixMultiplier.multiply();

        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        myfile << elapsed;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }

    myfile << "])\n";

}