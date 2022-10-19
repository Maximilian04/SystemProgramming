#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "fileIO.h"

namespace fileIO {
    void normalizeFileName(const char* const fileName, char* buffer);
    void setDefaultName(char* buffer);
    void setPostfix(char* buffer);
    bool hasCorrectPostfix(const char* const fileName, const size_t length);

    /**
     * @brief Write out machine code to file
     *
     * @param [in] asmCode AsmCode object
     * @param [in] fileName File name
     * @return Error Error code
     */
    Error writeAsmCode2File(AsmCode* asmCode, const char* const proposedFileName) {
        assert(asmCode != nullptr);
        assert(asmCode->code != nullptr);


        char fileName[MAX_FILENAME_SIZE] = {};
        normalizeFileName(proposedFileName, fileName);

        FILE* file = fopen(fileName, "wb");
        assert(file != nullptr);

        fwrite(&asmCode->pc, sizeof(size_t), 1,  file);
        fwrite(asmCode->code, sizeof(AsmCode_t), asmCode->pc, file);

        fclose(file);

        return Error::OK;
    }

    /**
     * @brief Set output file name to correct form
     *
     * @param [in] fileName Proposed file name
     * @param [out] buffer Buffer to write
     */
    void normalizeFileName(const char* const fileName, char* buffer) {
        assert(buffer != nullptr);
        if (fileName == nullptr)
            return fileIO::setDefaultName(buffer);

        size_t nameLength = strlen(fileName);
        if (nameLength == 0)
            return fileIO::setDefaultName(buffer);

        if (nameLength < (MAX_FILENAME_SIZE - 5)) {
            if (fileIO::hasCorrectPostfix(fileName, nameLength)) {
                strncpy(buffer, fileName, MAX_FILENAME_SIZE);
                return;
            }
        } else {
            nameLength = (MAX_FILENAME_SIZE - 5);
        }

        for (size_t i = 0; i < nameLength; ++i) {
            buffer[i] = fileName[i];
        }

        fileIO::setPostfix(buffer + nameLength);
    }

    /**
     * @brief Set the default output file name to buffer
     *
     * @param [out] buffer
     */
    void setDefaultName(char* buffer) {
        buffer[0] = 'a';
        setPostfix(buffer + 1);
    }

    /**
     * @brief Write file name postfix to buffer
     *
     * @param [out] buffer
     */
    void setPostfix(char* buffer) {
        buffer[0] = '.';
        buffer[1] = 'm';
        buffer[2] = 'a';
        buffer[3] = 'e';
        buffer[4] = '\0';
    }

    /**
     * @brief Does name have correct postfix
     *
     * @param [in] fileName
     * @param [in] length
     * @return true If name has correct postfix
     */
    bool hasCorrectPostfix(const char* const fileName, const size_t length) {
        if (fileName[length] != '\0') return false;
        if (fileName[length - 1] != 'e') return false;
        if (fileName[length - 1] != 'a') return false;
        if (fileName[length - 1] != 'm') return false;
        if (fileName[length - 1] != '.') return false;
        return true;
    }
};