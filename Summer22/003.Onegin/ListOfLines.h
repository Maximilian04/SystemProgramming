/**
 * @file ListOfLines.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Struct for store big text in one buffer
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LISTOFLINES_H
#define LISTOFLINES_H

/**
 * @brief One line
 * 
 */
struct Line {
    char* str;   ///< Stringed line
    int lenght;  ///< Lenght of line
};

/**
 * @brief List of separated lines
 * 
 */
struct ListOfLines {
    Line* lines;       ///< Lines
    char* firstVacant; ///< Pointer to memory to write
    int size;          ///< Number of lines in list
};

namespace listOfLines {
    int uploadList(ListOfLines* listPtr, const char* fileName);
    void destroyList(ListOfLines* listPtr);
}

#endif // LISTOFLINES_H
