//
// Created by user on 03.12.18.
//

#ifndef MATRIXMULTIPLIER2_MATRIXMULTIPLIER_H
#define MATRIXMULTIPLIER2_MATRIXMULTIPLIER_H


#include <cstdio>

class MatrixMultiplier2 {
private:
    double** MatrixA = nullptr, **MatrixB = nullptr, **MatrixC = nullptr;
    int nA, kA, nB, kB;
    int num_threads;
     char* filenameC;

public:
    MatrixMultiplier2( char* filenameA,  char* filenameB, int num_threads_,  char* filenameC_ = "C.txt");
    void multiply();
    void writeTo(double **Matrix);
    ~MatrixMultiplier2();
    void show();
private:
    void delete_matrix(double ***Matrix, int n);
    void read_MatrixA( char *fileName);
    void read_MatrixB( char *fileName);
    void write_matrix( char *filename, double **Matrix, int n, int k);
};


#endif //MATRIXMULTIPLIER2_MATRIXMULTIPLIER_H
