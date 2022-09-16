/**
 * @file pervert.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Pervertions over Evgeniy Onegin
 * @date 2022-08-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PERVERT_H
#define PERVERT_H

/**
 * @brief One line
 * 
 */
struct Line {
    char* str;   ///< Stringed line
    int lenght;  ///< Lenght of line
};

namespace pervert {
    /**
     * @brief List of separated lines
     * 
     */
    struct ListOfLines {
        Line* lines;       ///< Lines
        char* firstVacant; ///< Pointer to memory to write
        int size;          ///< Number of lines in list
    };

    extern ListOfLines listOfLines;    ///< List of separated lines
    extern ListOfLines listOfAlphabet; ///< List of separated characters

    /**
     * @brief Position in output file to write out
     * 
     */
    enum WritingPos {
        BEGIN, ///< Beginning of the file
        END,   ///< End of file
    };

    void sortLinesBeginning();
    void sortLinesReal();
    void sortLinesEnding();

    void writeOutPoem();

    void uploadAlphabet();
    void openOutFile();
    void closeOutFile();

    void readListOfLines();

    void destroyListOfLines();
    void destroyAlphabet();
}

#endif // PERVERT_H
