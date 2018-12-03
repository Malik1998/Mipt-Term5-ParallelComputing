#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MatrixMultiply/MatrixMultiplier.h"


int main(int argc, char **argv) {

    MatrixMultiplier matrixMultiplier(argv[1], argv[2],  atoi(argv[4]), argv[3]);
    matrixMultiplier.multiply();
}


