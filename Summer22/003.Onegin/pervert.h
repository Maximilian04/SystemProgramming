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

#include "cmdParser\cmdParser.h"
#include "ListOfLines.h"

namespace pervert {
    extern ListOfLines linesOfPoem;    ///< List of separated lines
    extern ListOfLines linesOfAlphabet; ///< List of separated characters

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

    int uploadPoem();
    int uploadAlphabet();

    void  openOutFile();
    void closeOutFile();

    void destroyAll();
    void destroyPoem();
    void destroyAlphabet();

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
}

#endif // PERVERT_H
