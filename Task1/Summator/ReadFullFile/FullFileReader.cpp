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
#include <cstdlib>

namespace FullFileReader {
    int readFullFile(const char *FileName, char ** text) {
        FILE *f = fopen(FileName, "rb");
        if (fseek(f, 0, SEEK_END)) {
            return 1;
        }
        size_t size = static_cast<size_t>(ftell(f));
        if (fseek(f, 0, SEEK_SET)) {
            return 1;
        }
        if (!((*text) = (char *)malloc(sizeof(char) * (size + 1)))) {
            return 1;
        }
        if(fread(*text, size, 1, f)) {
           // return 1;
        }
        (*text)[size] = 0;
        fclose(f);
        return 0;
    }

    int changeSlashesToNulles(char *text, int ** indexes) {
        int countOfLines = 0;
        int i = 0;
        while (text[i] != '\0') {
            if (text[i] == '\n') {
                ++countOfLines;
            }
            ++i;
        }
        (*indexes) = new int[countOfLines + 1]; // may-be
        int k = 0;
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

    void outputInFile(int * indexes, const char *text, const char *FileName, int countOfLines, int typeOfWriting) {
        int fileDescriptor = open(FileName, typeOfWriting, 0666);
        for (int i = 0; i < countOfLines - 1; ++i) {
            write(fileDescriptor, text + indexes[i], strlen(&text[indexes[i]]));
            write(fileDescriptor, "\n", 1);
        }
        close(fileDescriptor);
    }
}