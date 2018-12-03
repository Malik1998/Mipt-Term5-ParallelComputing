//
// Created by user on 08.09.18.
//

#include <fcntl.h>
#include "gtest/gtest.h"
#include "iostream"
#include "../testGenerator/testGenerator.cpp"
#include "../../Summator/Summator.h"
#include <ctime>


TEST(SummatorTest, SimpleTest1) {

    size_t count_threads = 1;
    Summator summator("numbers.txt", count_threads);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    ASSERT_EQ(summator.getSum().toString(), "210");
}

TEST(SummatorTest, SimpleTestGeneration100_10_1) {

    size_t count_threads = 1;
    std::string answer = testGenerator::generate("SimpleTestGeneration100_10_1.txt", 100, 10);
    Summator summator("SimpleTestGeneration100_10_1.txt", count_threads);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    ASSERT_EQ(summator.getSum().toString(), answer);
}

TEST(SummatorTest, FewThreadsSimpleTestGeneration100_10_1) {

    size_t count_threads = 5;
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration100_10_1.txt", 100, 10);
    Summator summator("FewThreadsSimpleTestGeneration100_10_1.txt", count_threads);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    ASSERT_EQ(summator.getSum().toString(), answer);
}


TEST(SummatorTest, FewThreadsSimpleTestGeneration1000_100_1) {

    size_t count_threads = 10;
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration1000_100_1.txt", 1000, 100);
    Summator summator("FewThreadsSimpleTestGeneration1000_100_1.txt", count_threads);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    ASSERT_EQ(summator.getSum().toString(), answer);
}


TEST(SummatorTest, FewThreadsSimpleTestGeneration10000_1000_1) {

    size_t count_threads = 10;
    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10000, 1000);
    Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", count_threads);

    int errorCode = summator.calculate();

    ASSERT_EQ(errorCode, 0);

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
    }

    ASSERT_EQ(summator.getSum().toString(), answer);
}


TEST(SummatorTest, GraphDraw) {

    std::string answer = testGenerator::generate("FewThreadsSimpleTestGeneration10000_1000_1.txt", 10, 10);

    std::ofstream myfile;
    myfile.open ("graph.txt");
    int max_threads = 10;

    myfile << "ns = np.array([";
    for(size_t i = 1; i < max_threads; i++) {
        myfile << i;
        if (i + 1 != max_threads) {
            myfile << ", ";
        }
    }
    myfile << "])\n";


    myfile << "time = np.array([";
    for (size_t i = 1; i < max_threads; i++) {
        Summator summator("FewThreadsSimpleTestGeneration10000_1000_1.txt", i);
        using namespace std;
        clock_t begin = clock();
        int errorCode = summator.calculate();

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        myfile << elapsed_secs;
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