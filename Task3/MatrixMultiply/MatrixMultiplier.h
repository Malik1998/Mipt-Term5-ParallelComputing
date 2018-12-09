//
// Created by user on 03.12.18.
//

#ifndef MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
#define MATRIXMULTIPLIER_MATRIXMULTIPLIER_H


#include <cstdio>

class MatrixMultiplier {
private:
    double** MatrixA = nullptr, **MatrixB = nullptr, **MatrixC = nullptr;
    int nA = 0, kA = 0, nB = 0, kB = 0;
    int num_threads = 0;
    const char* filenameC;

public:
    MatrixMultiplier(const char* filenameA, const char* filenameB, int num_threads_, int &error, const char* filenameC_ = "C.txt");
    void multiply();
    ~MatrixMultiplier();
    void show();
private:
    void delete_matrix(double ***Matrix, int n);
    bool read_MatrixA(const char *fileName);
    bool read_MatrixB(const char *fileName);
    void write_matrix(const char *filename, double **Matrix, int n, int k);
};


#endif //MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
