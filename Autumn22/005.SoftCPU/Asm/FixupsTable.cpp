#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FixupsTable.h"

namespace fixupsTable {
    int getLabelIndex(FixupsTable* fixups, char* name);

    /**
     * @brief Free memory
     *
     * @param [out] fixups Fixups table
     */
    void freeTable(FixupsTable* fixups) {
        for (int i = 0; fixups->names[i] != nullptr; ++i) {
            free(fixups->names[i]);
            fixups->names[i] = nullptr;
        }
    }

    /**
     * @brief Set label to table
     *
     * @param [out] fixups Fixups table
     * @param [in] name Label name (will be copied)
     * @param [in] length Label name length (excluding \0)
     * @param [in] pc Program counter of label
     * @return Error Error code
     */
    Error setLabel(FixupsTable* fixups, char* name, int length, size_t pc) {
        int index = getLabelIndex(fixups, name);
        if (fixups->names[index]) {
        } else {
            fixups->names[index] = (char*)calloc(length + 1, sizeof(char));
            for (int i = 0; i < length; ++i) {
                fixups->names[index][i] = name[i];
            }
            fixups->names[index][length] = '\0';
        }

        fixups->pcTable[index] = pc;

        return Error::OK;
    }

    /**
     * @brief Get pc of the label
     *
     * @param [in] fixups Fixups table
     * @param [in] name Label name
     * @param [in] length Label name length (excluding \0)
     * @return size_t Program counter of label
     */
    size_t getLabelPC(FixupsTable* fixups, char* name, int length) {
        int index = getLabelIndex(fixups, name);

        if (fixups->names[index]) {
            return fixups->pcTable[index];
        } else {
            return 0;
        }
        length = length ? 0 : 0;
    }

    /**
     * @brief Get index of the label with **name** or (size) if it is new label
     *
     * @param [in] fixups Fixups table
     * @param [in] name Label name
     * @return int Index or (size)
     */
    int getLabelIndex(FixupsTable* fixups, char* name) {
        int i = 0;
        for (; fixups->names[i] != nullptr; ++i) {
            if (strcmp(fixups->names[i], name) == 0)
                return i;
        }
        return i;
    }
}
