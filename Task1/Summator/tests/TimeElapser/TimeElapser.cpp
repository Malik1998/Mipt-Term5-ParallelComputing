//
// Created by user on 02.12.18.
//

#include <fstream>
#include "../../Summator/Summator.h"
#include "../testGenerator/testGenerator.cpp"
#include <time.h>

int main() {
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10000, 10000);

    std::ofstream myfile;
    myfile.open ("graph.txt");
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
        Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", i, error);

        if (error) {
            return 1;
        }

        struct timespec start, finish;
        double elapsed;

        clock_gettime(CLOCK_MONOTONIC, &start);

        int errorCode = summator.calculate();

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