/**
 * @file LabelsTable.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Table with assembler's labels
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <..\AsmCode.h>

#ifndef LABEL_TABLE_SIZE
#define LABEL_TABLE_SIZE (128)
#endif // LABEL_TABLE_SIZE
static const int COMNAME_BUFFER_SIZE = 64;

struct LabelsTable {
    char* names[LABEL_TABLE_SIZE];
    size_t pcTable[LABEL_TABLE_SIZE];
};

namespace labelsTable {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,    ///< No errors
    };

    void freeTable(LabelsTable* labels);
    Error setLabel(LabelsTable* labels, char* name, int length, size_t pc);
    size_t getLabelPC(LabelsTable* labels, char* name, int length);
}

#endif // LABELTABLE_H
