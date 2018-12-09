//
// Created by user on 08.09.18.
//

#include <fcntl.h>
#include "gtest/gtest.h"
#include "iostream"
#include "../testGenerator/testGenerator.cpp"
#include "../../Summator/Summator.h"
#include <ctime>
#include <time.h>


TEST(SummatorTest, SimpleTest1) {

    int count_threads = 1;
    int error;
    Summator summator("numbers.txt", count_threads, error);
    ASSERT_EQ(error, 0);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    std::string a;
    summator.getSumString(a);
    ASSERT_EQ(a, "210");
}

TEST(SummatorTest, SimpleTestGeneration100_10_1) {

    int count_threads = 1;
    std::string answer = testGenerator::generate("SimpleTestGeneration100_10_1.txt", 100, 10);

    int error;
    Summator summator("SimpleTestGeneration100_10_1.txt", count_threads, error);
    ASSERT_EQ(error, 0);


    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    std::string a;
    summator.getSum().toString(a);
    ASSERT_EQ(a, answer);
}

TEST(SummatorTest, FewThreadsSimpleTestGeneration100_10_1) {

    int count_threads = 5;

    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration100_10_1.txt", 100, 10);

    int error;
    Summator summator("FewThreadsSimpleTestGeneration100_10_1.txt", count_threads, error);
    ASSERT_EQ(error, 0);


    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    std::string a;
    summator.getSum().toString(a);
    ASSERT_EQ(a, answer);
}


TEST(SummatorTest, FewThreadsSimpleTestGeneration1000_100_1) {

    int count_threads = 10;
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration1000_100_1.txt", 10, 1);

    int error;
    Summator summator("FewThreadsSimpleTestGeneration1000_100_1.txt", count_threads, error);
    ASSERT_EQ(error, 0);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    std::string a;
    summator.getSum().toString(a);
    ASSERT_EQ(a, answer);
}


TEST(SummatorTest, FewThreadsSimpleTestGeneration10000_1000_1) {

    int count_threads = 10;
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10000, 1000);


    int error;
    Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", count_threads, error);
    ASSERT_EQ(error, 0);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    std::string a;
    summator.getSum().toString(a);
    ASSERT_EQ(a, answer);
}


TEST(SummatorTest, GraphDraw) {

    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10, 10);

    std::ofstream myfile;
    myfile.open ("graph.txt");
    int max_threads = 10;

    myfile << "ns = np.array([";
    for(int i = 1; i < max_threads; i++) {
        myfile << i;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }
    myfile << "])\n";


    myfile << "time = np.array([";
    for (int i = 1; i < max_threads; i++) {
        int error;
        Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", i, error);
        ASSERT_EQ(error, 0);
        using namespace std;

        struct timespec start, finish;
        double elapsed;

        clock_gettime(CLOCK_MONOTONIC, &start);

        int errorCode = summator.calculate();

        clock_gettime(CLOCK_MONOTONIC, &finish);

        ASSERT_EQ(errorCode, 0);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        myfile << elapsed;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }

    myfile << "])\n";

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}