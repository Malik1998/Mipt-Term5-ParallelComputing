#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MatrixMultiply/MatrixMultiplier.h"


int main(int argc, char **argv) {

    try {
        int error;
        MatrixMultiplier matrixMultiplier(argv[1], argv[2],  1, error, argv[3]);
        if (!error) {
            std::cerr << "Some error occured on costructing" << std::endl;
            return 1;
        }
        matrixMultiplier.multiply();
    } catch (std::bad_alloc &error) {
        std::cerr << "Exception on Memory allocation";
    }


}


