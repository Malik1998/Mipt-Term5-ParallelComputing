//
// Created by user on 03.12.18.
//

#include <fstream>
#include "MatrixMultiplier.h"

MatrixMultiplier::MatrixMultiplier(const char *filenameA, const char *filenameB, int num_threads_, int &error, const char *filenameC_) :
                num_threads(num_threads_), filenameC(filenameC_) {

    if (!read_MatrixA(filenameA)) {
        error = 1;
        return ;
    }

    if (!read_MatrixB(filenameB)) {
        error = 1;
        return ;
    }

    MatrixC = new (std::nothrow) double*[nA];

    if (!MatrixC) {
        error = 1;
        return;
    }

    for (int i = 0; i < nA; i++) {
        MatrixC[i] = new (std::nothrow) double[kB];
        if (!MatrixC[i]) {
            error = 1;
            return ;
        }
    }

    error = 0;
}

void MatrixMultiplier::delete_matrix(double ***Matrix, int n) {
    try{
        for (int i = 0; i < n; i++) {
            delete[] (*Matrix)[i];
        }
        delete[] (*Matrix);
    } catch (...) {
        throw ;
    }

}

bool MatrixMultiplier::read_MatrixA(const char *fileName) {
    std::ifstream file;
    file.open (fileName);
    file >> nA >> kA;

    MatrixA = new (std::nothrow) double*[nA];

    if (!MatrixA) {
        return false;
    }

    for (int i = 0; i < nA; i++) {
        MatrixA[i] = new (std::nothrow) double[kA];

        if (!MatrixA[i]) {
            return false;
        }

        for (int j = 0; j < kA; j++) {
            file >> MatrixA[i][j];
        }
    }

    file.close();
    return true;
}

bool MatrixMultiplier::read_MatrixB(const char *fileName) {
    std::ifstream file;
    file.open (fileName);
    file >> nB >> kB;

    MatrixB = new (std::nothrow) double*[nB];

    if (!MatrixB) {
        return false;
    }

    for (int i = 0; i < nB; i++) {
        MatrixB[i] = new (std::nothrow) double[kB];

        if (!MatrixB[i]) {
            return false;
        }

        for (int j = 0; j < kB; j++) {
            file >> MatrixB[i][j];
        }
    }

    file.close();
    return true;
}

void MatrixMultiplier::write_matrix(const char *filename, double **Matrix, int n, int k) {
    std::ofstream file;
    file.open(filename);
    file << n << " " << k << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            file << Matrix[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}

void MatrixMultiplier::multiply() {
#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < kB; j++) {
            MatrixC[i][j] = 0;
            for (int k = 0; k < kA; k++) {
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
}

MatrixMultiplier::~MatrixMultiplier() {
    delete_matrix(&MatrixA, nA);

    delete_matrix(&MatrixB, nB);

    delete_matrix(&MatrixC, nA);
}

void MatrixMultiplier::show() {
    write_matrix(filenameC, MatrixC, nA, kB);
}
