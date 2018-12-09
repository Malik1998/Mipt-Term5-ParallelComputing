//
// Created by user on 03.12.18.
//

#include <fstream>
#include "MatrixMultiplier2.h"

MatrixMultiplier2::MatrixMultiplier2( char *filenameA,  char *filenameB, int num_threads_,  char *filenameC_) :
                num_threads(num_threads_), filenameC(filenameC_) {

    try {
        read_MatrixA(filenameA);

        read_MatrixB(filenameB);

        MatrixC = new double*[nA];
        for (int i = 0; i < nA; i++) {
            MatrixC[i] = new double[kB];
        }
    } catch (std::bad_alloc &error) {
        throw;
    }
}

void MatrixMultiplier2::delete_matrix(double ***Matrix, int n) {
    try{
        for (int i = 0; i < n; i++) {
            delete[] (*Matrix)[i];
        }
        delete[] (*Matrix);
    } catch (...) {
        throw ;
    }

}

void MatrixMultiplier2::read_MatrixA( char *fileName) {
    std::ifstream myfile;
    myfile.open(fileName, std::ifstream::binary);

    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&nA)), sizeof(nA));
    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&kA)), sizeof(kA));

    MatrixA = new double*[nA];

    for(int i = 0; i < nA; i++) {
            MatrixA[i] = new double[kA];
    }


    for (size_t i = 0; i < nA; i++) {
        for (size_t j = 0; j < kA; j++) {
            double a = 0;
            myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&a)), sizeof(double));
            MatrixA[i][j] = a;
        }
    }
    myfile.close();
}

void MatrixMultiplier2::read_MatrixB( char *fileName) {
    std::ifstream myfile;
    myfile.open(fileName, std::ifstream::binary);

    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&nB)), sizeof(nB));
    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&kB)), sizeof(kB));

    MatrixB = new double*[nB];

    for(int i = 0; i < nB; i++) {
            MatrixB[i] = new double[kB];
    }

    for (size_t i = 0; i < nB; i++) {
        for (size_t j = 0; j < kB; j++) {
            double a = 0;
            myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&a)), sizeof(double));
            MatrixB[i][j] = a;
        }
    }
    myfile.close();
}

void MatrixMultiplier2::write_matrix( char *filename, double **Matrix, int n, int k) {
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

void MatrixMultiplier2::multiply() {
//#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < kB; j++) {
            MatrixC[i][j] = 0;
            for (int k = 0; k < kA; k++) {
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
}

MatrixMultiplier2::~MatrixMultiplier2() {
    delete_matrix(&MatrixA, nA);

    delete_matrix(&MatrixB, nB);

    delete_matrix(&MatrixC, nA);
}

void MatrixMultiplier2::show() {
    write_matrix(filenameC, MatrixC, nA, kB);
}
void MatrixMultiplier2::writeTo(double **Matrix) {
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < kB; j++) {
            Matrix[i][j] = MatrixC[i][j];
        }
    }
}
