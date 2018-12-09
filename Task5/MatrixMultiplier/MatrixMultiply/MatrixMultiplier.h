//
// Created by user on 03.12.18.
//

#ifndef MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
#define MATRIXMULTIPLIER_MATRIXMULTIPLIER_H


#include <cstdio>

class MatrixMultiplier {
private:
    double** MatrixA, **MatrixB, **MatrixC;
    int nA, kA, nB, kB;
    int count_process, index;
    char* filenameC;

public:
    MatrixMultiplier(char *filenameA, char *filenameB, char *filenameC_, int i,
                         int i1);
    void multiply();
    ~MatrixMultiplier();

    void writeTo(double **Matrix);

    void show(char *filename);

    double get(int i, int i1);

private:
    void delete_matrix(double ***Matrix, int n);
    void read_Matrix(char *fileName, double ***matrix, int &n, int &k);
    void write_matrix(char *filename, double **Matrix, int n, int k);
};


#endif //MATRIXMULTIPLIER_MATRIXMULTIPLIER_H
