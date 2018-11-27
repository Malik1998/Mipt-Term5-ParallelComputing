//
// Created by user on 13.09.18.
//

#include <cstdio>
#include <sys/stat.h>
#include <zconf.h>
#include <iostream>
#include "FullFileReader.h"
#include <fcntl.h>
#include <stdio.h>
#include <cstring>

namespace FullFileReader {
    void readFullFile(const char *FileName, char ** text) {
        int fileDescriptor = open(FileName, O_RDONLY);
        struct stat st;
        fstat(fileDescriptor, &st);
        auto fullTextSize = static_cast<size_t>(st.st_size);
        (*text) = new char[fullTextSize + 1]; // Maybe - maybe
        read(fileDescriptor, *text, fullTextSize);
        close(fileDescriptor);
    }

    size_t changeSlashesToNulles(char *text, size_t ** indexes) {
        size_t countOfLines = 0;
        size_t i = 0;
        while (text[i] != '\0') {
            if (text[i] == '\n') {
                ++countOfLines;
            }
            ++i;
        }
        (*indexes) = new size_t[countOfLines + 1]; // may-be
        size_t k = 0;
        i = 0;
        countOfLines = 0;
        while (text[i] != '\0') {
            if (text[i] == '\n') {
                (*indexes)[countOfLines++] = k;
                k = i + 1;
                text[i] = '\0';
            }
            ++i;
        }
        return countOfLines;
    }

    void outputInFile(size_t * indexes, const char *text, const char *FileName, size_t countOfLines, int typeOfWriting) {
        int fileDescriptor = open(FileName, typeOfWriting, 0666);
        for (size_t i = 0; i < countOfLines - 1; ++i) {
            write(fileDescriptor, text + indexes[i], strlen(&text[indexes[i]]));
            write(fileDescriptor, "\n", 1);
        }
        close(fileDescriptor);
    }
}