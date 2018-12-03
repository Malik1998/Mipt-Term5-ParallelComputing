//
// Created by user on 03.12.18.
//

#include <fstream>
#include "MatrixMultiplier.h"

MatrixMultiplier::MatrixMultiplier(const char *filenameA, const char *filenameB, size_t num_threads_, const char *filenameC_) :
                num_threads(num_threads_), filenameC(filenameC_) {

    read_Matrix(filenameA, &MatrixA, nA, kA);

    read_Matrix(filenameB, &MatrixB, nB, kB);

   MatrixC = new double*[nA];

    for (size_t i = 0; i < nA; i++) {
        MatrixC[i] = new double[kB];
    }
}

void MatrixMultiplier::delete_matrix(double ***Matrix, size_t n) {
    for (size_t i = 0; i < n; i++) {
        delete[] (*Matrix)[i];
    }

    delete[] (*Matrix);
}

void MatrixMultiplier::read_Matrix(const char *fileName, double ***matrix, size_t &n, size_t &k) {
    std::ifstream file;
    file.open (fileName);
    file >> n >> k;

    (*matrix) = new double*[n];

    for (size_t i = 0; i < n; i++) {
        (*matrix)[i] = new double[k];
        for (size_t j = 0; j < k; j++) {
            file >> (*matrix)[i][j];
        }
    }

    file.close();
}

void MatrixMultiplier::write_matrix(const char *filename, double **Matrix, size_t n, size_t k) {
    std::ofstream file;
    file.open(filename);
    file << n << " " << k << "\n";
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < k; j++) {
            file << Matrix[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}

void MatrixMultiplier::multiply() {
    for (size_t i = 0; i < nA; i++) {
        for (size_t j = 0; j < kB; j++) {
            MatrixC[i][j] = 0;
#pragma omp parallel for num_threads(num_threads)
            for (size_t k = 0; k < kA; k++) {
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }

    write_matrix(filenameC, MatrixC, nA, kB);
}

MatrixMultiplier::~MatrixMultiplier() {
    delete_matrix(&MatrixA, nA);

    delete_matrix(&MatrixB, nB);

    delete_matrix(&MatrixC, nA);
}