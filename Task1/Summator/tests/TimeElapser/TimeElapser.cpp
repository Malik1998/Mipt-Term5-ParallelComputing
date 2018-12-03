//
// Created by user on 02.12.18.
//

#include <fstream>
#include "../../Summator/Summator.h"
#include "../testGenerator/testGenerator.cpp"

int main() {
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10000, 10000);

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
        Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", i);
        using namespace std;
        clock_t begin = clock();
        int errorCode = summator.calculate();

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        myfile << elapsed_secs;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }

    myfile << "])\n";

}