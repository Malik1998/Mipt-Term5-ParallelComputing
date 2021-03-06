#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MatrixMultiply/MatrixMultiplier.h"
#include "MatrixMultiplier2/MatrixMultiplier2.h"
#include "mpi.h"
#include "testGenerator/testGenerator.cpp"


int main(int argc, char **argv) {


    double **answ;

    MPI_Init(&argc,&argv);

    int nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MatrixMultiplier *matrixMultiplier;

    try {
        matrixMultiplier = new MatrixMultiplier(argv[1], argv[2], argv[3], nproc, rank);
    } catch (std::bad_alloc &error) {
        std::cerr << "Allocation error" << std::endl;
        MPI_Finalize();
        delete matrixMultiplier;
        return 1;
    } catch (...) {
        std::cerr << "Another error" << std::endl;
        MPI_Finalize();
        delete matrixMultiplier;
        return 2;
    }

    try {
        matrixMultiplier->multiply();
        delete matrixMultiplier;
    } catch (std::bad_alloc &error) {
        std::cerr << "Allocation error" << std::endl;
        MPI_Finalize();
        delete matrixMultiplier;
        return 1;
    } catch (...) {
        std::cerr << "Another error" << std::endl;
        MPI_Finalize();
        delete matrixMultiplier;
        return 2;
    }

    MPI_Finalize();
}


