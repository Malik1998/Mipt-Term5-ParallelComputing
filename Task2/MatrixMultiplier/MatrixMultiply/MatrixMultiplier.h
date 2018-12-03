//
// Created by user on 03.12.18.
//

#ifndef MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
#define MATRIXMULTIPLIER_MATRIXMULTIPLIER_H


#include <cstdio>

class MatrixMultiplier {
private:
    double** MatrixA, **MatrixB, **MatrixC;
    size_t nA, kA, nB, kB;
    size_t num_threads;
    const char* filenameC;

public:
    MatrixMultiplier(const char* filenameA, const char* filenameB, size_t num_threads_, const char* filenameC_ = "C.txt");
    void multiply();
    ~MatrixMultiplier();
private:
    void delete_matrix(double ***Matrix, size_t n);
    void read_Matrix(const char *fileName, double ***matrix, size_t &n, size_t &k);
    void write_matrix(const char *filename, double **Matrix, size_t n, size_t k);
};


#endif //MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
