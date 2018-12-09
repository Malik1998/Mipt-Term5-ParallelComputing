//
// Created by user on 03.12.18.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "MatrixMultiplier.h"
#include "mpi.h"

MatrixMultiplier::MatrixMultiplier(char *filenameA, char *filenameB,
        char *filenameC_ = "c.txt", int count = 1, int rank = 0)  :
                filenameC(filenameC_), count_process(count), index(rank) {

    read_Matrix(filenameA, &MatrixA, nA, kA);

    read_Matrix(filenameB, &MatrixB, nB, kB);

    MatrixC = new double*[nA];

    for (int i = 0; i < nA; i++) {
        MatrixC[i] = new double[kB];
    }
}

void MatrixMultiplier::delete_matrix(double ***Matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] (*Matrix)[i];
    }

    delete[] (*Matrix);
}

void MatrixMultiplier::read_Matrix(char *fileName, double ***matrix, int &n, int &k) {

    MPI_File cFile;

    if (MPI_File_open(MPI_COMM_WORLD, fileName,
                  MPI_MODE_RDWR| MPI_MODE_CREATE, MPI_INFO_NULL,
                  &cFile ) != 0) {
        std::cerr << "Error on opening!" << std::endl;
        return;
    }

    MPI_Status status_read;
    memset( &status_read, 0xff, sizeof(MPI_Status) );

    int *buf = (int *)malloc( 1 * sizeof(int) );
    MPI_File_read(cFile, buf, 1, MPI_INT, &status_read);
    n = buf[0];

    MPI_File_read(cFile, buf, 1, MPI_INT, &status_read);
    k = buf[0];

    (*matrix) = new double*[n];
    for (int i = 0; i < n; i++) {
        (*matrix)[i] = new double[k];
        for (int j = 0; j < k; j++) {
            MPI_File_read(cFile, &((*matrix)[i])[j], 1, MPI_DOUBLE, &status_read);
        }
    }

    MPI_File_close( &cFile );

}

void MatrixMultiplier::write_matrix(char *filename, double **Matrix, int n, int k) {

    MPI_File cFile;

    MPI_File_open(MPI_COMM_WORLD, filename,
                  MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL,
                  &cFile );

    if (index == 0) {
        MPI_File_write(cFile, &nA, 1, MPI_INT, NULL);
     //   MPI_File_seek(cFile, sizeof(int), MPI_SEEK_CUR);
        MPI_File_write(cFile, &kB, 1, MPI_INT, NULL);
     //   MPI_File_seek(cFile, sizeof(int), MPI_SEEK_CUR);
    }
  //  std::cout << index << " " << n << " " << kB << std::endl;
    if (index != 0) {
        MPI_File_seek(cFile, sizeof(int) * 2, MPI_SEEK_CUR);
        MPI_File_seek(cFile, sizeof(double) * n * kB, MPI_SEEK_CUR);
    }
    for (int i = n; i < k; i++) {
        for (int j = 0; j < kB; j++) {
            MPI_File_write(cFile, &Matrix[i][j], 1, MPI_DOUBLE, NULL);
       //     MPI_File_seek(cFile, sizeof(double), MPI_SEEK_CUR);
        }
     //   std::cout << std::endl;
    }

    MPI_File_close( &cFile );
}

void MatrixMultiplier::multiply() {
    
    int l_line = (nA / count_process) * index;
    int r_line = (nB / count_process) * (index + 1);

    if ((index + 1) == count_process ) {
        r_line = nA;
    }

#pragma omp parallel for collapse(2)
    for (int i = l_line; i < r_line; i++) {
        for (int j = 0; j < kB; j++) {
            MatrixC[i][j] = 0;
            for (int k = 0; k < kA; k++) {
                MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }

    write_matrix(filenameC, MatrixC, l_line, r_line);
}

MatrixMultiplier::~MatrixMultiplier() {
    delete_matrix(&MatrixA, nA);

    delete_matrix(&MatrixB, nB);

    delete_matrix(&MatrixC, nA);
}

void MatrixMultiplier::show(char *filename) {
    std::ifstream myfile;
    myfile.open(filename, std::ifstream::binary);

    int n, k;
    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&n)), sizeof(n));
    myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&k)), sizeof(k));

    std::cout << n << " " << k << std::endl;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < k; j++) {
            double a = 0;
            myfile.read(const_cast<char *>(reinterpret_cast<const char*>(&a)), sizeof(double));
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }
    myfile.close();
}

void MatrixMultiplier::writeTo(double **Matrix) {
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < kB; j++) {
            Matrix[i][j] = MatrixC[i][j];
        }
    }
}

double MatrixMultiplier::get(int i, int i1) {
    return MatrixC[i][i1];
}
