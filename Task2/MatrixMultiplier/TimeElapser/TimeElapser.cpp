//
// Created by user on 02.12.18.
//

#include <fstream>
#include "../testGenerator/testGenerator.cpp"
#include "../MatrixMultiply/MatrixMultiplier.h"

int main() {
    testGenerator::generate("A.txt", 1000, 1000);
    testGenerator::generate("B.txt", 1000, 1000);

    std::ofstream myfile;
    myfile.open ("graph.txt");
    int max_threads = 10;

    myfile << "ns = np.array([";
    for(size_t i = 1; i < max_threads; i++) {
        myfile << i;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }
    myfile << "])\n";


    myfile << "time = np.array([";
    for (size_t i = 1; i < max_threads; i++) {

        MatrixMultiplier matrixMultiplier("A.txt", "B.txt", i, "C.txt");

        clock_t begin = clock();

        matrixMultiplier.multiply();

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        myfile << elapsed_secs;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }

    myfile << "])\n";

}