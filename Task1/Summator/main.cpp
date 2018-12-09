#include <iostream>
#include "Summator/Summator.h"

int main(int argc, char **argv) {
    int number = atoi(argv[2]);

    int error = 0;

    Summator summator(argv[1], number, error);

    int errorCode = summator.calculate();

    if (errorCode) {
        std::cerr << "Error while calculating" << std::endl;
        return errorCode;
    }


    summator.getSum().show();
}