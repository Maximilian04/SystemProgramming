/**
 * @file voice.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Utilities for voice module
 * @date 2022-12-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef VOICE_H
#define VOICE_H

namespace voice {
    void clear();

    void addText(char const* str);

    void generate();
}

#endif // VOICE_H
