#include <iostream>
#include <fstream>


void read_Matrix(const char *fileName, double ***matrix, size_t& i, size_t& i1);

void write_matrix(const char *filename, double **Matrix, size_t i, size_t i1);

void delete_matrix(double **Matrix, size_t n);

int main(int argc, char **argv) {

    size_t nA, kA;
    double **MatrixA;

    read_Matrix(argv[1], &MatrixA, nA, kA);


    size_t nB, kB;
    double **MatrixB;

    read_Matrix(argv[2], &MatrixB, nB, kB);

    double **MatrixC = new double*[nA];

    for (size_t i = 0; i < nA; i++) {
        MatrixC[i] = new double[kB];
    }


    for (size_t i = 0; i < nA; i++) {

        #pragma omp parallel for

        for (size_t j = 0; j < kB; j++) {
            double c_ij = 0;
            for (size_t k = 0; k < kA; k++) {
                c_ij += MatrixA[i][k] * MatrixB[k][j];
            }
            MatrixC[i][j] = c_ij;
        }
    }

    write_matrix(argv[3], MatrixC, nA, kB);

    delete_matrix(MatrixA, nA);
    delete[] MatrixA;

    delete_matrix(MatrixB, nB);
    delete[] MatrixB;

    delete_matrix(MatrixB, nA);
    delete[] MatrixC;

}

void delete_matrix(double **Matrix, size_t n) {
    for (size_t i = 0; i < n; i++) {
        delete[] Matrix[i];
    }
}

void write_matrix(const char *filename, double **Matrix, size_t n, size_t k) {

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

void read_Matrix(const char *fileName, double ***matrix, size_t &n, size_t &k) {

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