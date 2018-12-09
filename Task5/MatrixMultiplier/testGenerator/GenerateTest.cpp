//
// Created by user on 07.12.18.
//

#include <cstdlib>
#include "testGenerator.cpp"

int main(int argc, char **argv) {

    try {
        int n = atoi(argv[1]);
        int k = atoi(argv[2]);
        int m = atoi(argv[3]);

        double **answ = new double*[n];
        for (int i = 0; i < n; i++) {
            answ[i] = new double[m];
        }
        testGenerator::gener("a.txt", "b.txt", n, k, m, answ);
        std::ofstream myfile;
        myfile.open ("c.txt");

        myfile.write(reinterpret_cast<char*>(&n), sizeof(int));
        myfile.write(reinterpret_cast<char*>(&m), sizeof(int));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                myfile.write(reinterpret_cast<char*>(&answ[i][j]), sizeof(double));
            }
        }
        myfile.close();
    } catch (std::bad_alloc &error) {
        std::cerr << "Allocation error" << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Another error" << std::endl;
        return 2;
    }

}