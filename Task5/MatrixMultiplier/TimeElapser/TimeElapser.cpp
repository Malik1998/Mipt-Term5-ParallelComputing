//
// Created by user on 02.12.18.
//

#include <fstream>
#include <iostream>
#include "mpi.h"
#include "../MatrixMultiply/MatrixMultiplier.h"

int main(int argc, char **argv) {

    double **answ;

    MPI_Init(NULL, NULL);

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
    //   std::cout << rank << std::endl;
    //matrixMultiplier.test();

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t begin;
    if (rank == 0) {
        begin = clock();

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

    if(rank == 0) {
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << nproc << " " << elapsed_secs << std::endl;
    }

}