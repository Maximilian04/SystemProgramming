/**
 * @file FixupsTable.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Table with assembler's fixups
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef FIXUPSTABLE
#define FIXUPSTABLE

#include <..\AsmCode.h>

#ifndef FIXUPS_TABLE_SIZE
#define FIXUPS_TABLE_SIZE (128)
#endif // FIXUPS_TABLE_SIZE
static const int COMNAME_BUFFER_SIZE = 64;

struct FixupsTable {
    char* names[FIXUPS_TABLE_SIZE];
    size_t pcTable[FIXUPS_TABLE_SIZE];
};

namespace fixupsTable {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,    ///< No errors
    };

    void freeTable(FixupsTable* fixups);
    Error setLabel(FixupsTable* fixups, char* name, int length, size_t pc);
    size_t getLabelPC(FixupsTable* fixups, char* name, int length);
}

#endif // FIXUPSTABLE
