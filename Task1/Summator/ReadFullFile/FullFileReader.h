//
// Created by user on 13.09.18.
//

#ifndef STRINGSORTING_FULLFILEREADER_H
#define STRINGSORTING_FULLFILEREADER_H

/// Change full file into variable and manupulate with it
namespace FullFileReader {
    /// read file to text pointer
    /// \param FileName - name of the file to be read
    /// \param text - variable, that will point to text
    void readFullFile(const char *FileName, char ** text);

    /// change \n to \0
    /// \param text - variable pointing to text, where \n to be changed
    /// \param indexes - array where elemnts will index to the new tokens
    /// \return count of elemnts in indexes
    size_t changeSlashesToNulles(char *text, size_t ** indexes);


    /// write text to file with order written in indexes array to the FileName file
    /// \param indexes  - array with order
    /// \param text - text where we will read
    /// \param FileName - file where to safe file
    /// \param countOfLines - count of elements in indexes
    /// \param typeOfWriting - parametres to open the file
    void outputInFile(size_t * indexes, const char *text, const char *FileName, size_t countOfLines, int typeOfWriting);
};


#endif //STRINGSORTING_FULLFILEREADER_H
