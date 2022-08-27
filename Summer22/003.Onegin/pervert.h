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
    char* str;  ///< Stringed line
    int lenght; ///< Lenght of line
};

namespace pervert {
    const int BUFFER_SIZE = 256;        ///< Size of buffer for one line
#define       BUFFER_SIZE_ "256"        ///< Size of buffer for one line
    const int EXTRA_BUFFER_SIZE = 2048; ///< Size of buffer for one bigger line
#define       EXTRA_BUFFER_SIZE_ "2048" ///< Size of buffer for one bigger line
    const int MAX_LINE_NUMBER = 9000;   ///< Size of list with lines

    /**
     * @brief List of separated lines
     * 
     */
    struct ListOfLines {
        Line* lines; ///< Lines
        int size;                    ///< Number of lines in list
    };

    extern ListOfLines listOfLines; ///< List of separated lines
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
    void sortLinesEnding();

    void writeOutPoem(WritingPos pos);

    void uploadAlphabet();
    void openOutFile();
    void closeOutFile();

    void readListOfLines();
    void destroyListOfLines();
}

#endif // PERVERT_H
