//
// Created by user on 07.12.18.
//

#include <cstddef>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

    char *fileName = argv[1];
    std::ifstream myfile;
    myfile.open(fileName);

    char *fileName2 = argv[2];
    std::ifstream myfile2;
    myfile2.open(fileName2);

    int nA = 0, kA = 0;

    myfile.read(reinterpret_cast<char *>(&nA), sizeof(int));
    std::cout <<fileName << " " << nA << std::endl;

    myfile2.read(reinterpret_cast<char *>(&nA), sizeof(int));
    std::cout <<fileName2 << " " << nA << std::endl;

    myfile2.read(reinterpret_cast<char *>(&kA), sizeof(int));
    std::cout <<fileName2 << " " << kA << std::endl;

    myfile.read(reinterpret_cast<char *>(&kA), sizeof(int));
    std::cout <<fileName << " " << kA << std::endl;

    for (size_t i = 0; i < nA; i++) {
        for (size_t j = 0; j < kA; j++) {
            double a = 0;
            double b = 0;
            myfile.read(const_cast<char *>(reinterpret_cast<const char *>(&a)), sizeof(double));
            myfile2.read(const_cast<char *>(reinterpret_cast<const char *>(&b)), sizeof(double));
            if (a != b) {
                std::cerr << a << " " << b << std::endl;
            }
        }
    }
    myfile.close();
    myfile2.close();

    return 0;
}