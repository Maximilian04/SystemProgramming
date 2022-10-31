#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LabelsTable.h"

namespace labelsTable {
    int getLabelIndex(LabelsTable* labels, char* name);

    /**
     * @brief Free memory
     *
     * @param [out] labels Fixups table
     */
    void freeTable(LabelsTable* labels) {
        for (int i = 0; labels->labels[i].name != nullptr; ++i) {
            free(labels->labels[i].name);
            labels->labels[i].name = nullptr;
        }
    }

    /**
     * @brief Set label to table
     *
     * @param [out] labels Fixups table
     * @param [in] name Label name (will be copied)
     * @param [in] length Label name length (excluding \0)
     * @param [in] pc Program counter of label
     * @return Error Error code
     */
    Error setLabel(LabelsTable* labels, char* name, int length, size_t pc) {
        int index = getLabelIndex(labels, name);
        if (labels->labels[index].name) {
        } else {
            labels->labels[index].name = (char*)calloc(length + 1, sizeof(char));
            for (int i = 0; i < length; ++i) {
                labels->labels[index].name[i] = name[i];
            }
            labels->labels[index].name[length] = '\0';
        }

        labels->labels[index].pc = pc;

        return Error::OK;
    }

    /**
     * @brief Get pc of the label
     *
     * @param [in] labels Fixups table
     * @param [in] name Label name
     * @param [in] length Label name length (excluding \0)
     * @return size_t Program counter of label
     */
    size_t getLabelPC(LabelsTable* labels, char* name, int length) {
        int index = getLabelIndex(labels, name);

        if (labels->labels[index].name) {
            return labels->labels[index].pc;
        } else {
            return 0;
        }
        length = length ? 0 : 0;
    }

    /**
     * @brief Get index of the label with **name** or (size) if it is new label
     *
     * @param [in] labels Fixups table
     * @param [in] name Label name
     * @return int Index or (size)
     */
    int getLabelIndex(LabelsTable* labels, char* name) {
        int i = 0;
        for (; labels->labels[i].name != nullptr; ++i) {
            if (strcmp(labels->labels[i].name, name) == 0)
                return i;
        }
        return i;
    }
}
