/**
 * @file texts.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Texts foor program
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef TEXTS_H
#define TEXTS_H

namespace texts {
    const wchar_t GUESS_INVITE_L[] = L""
        "I can help you find music that is suitable for you. Please, answer me only with yes or no.";
    const char GUESS_INVITE[] = ""
        "I can help you find music that is suitable for you. Please, answer me only with yes or no.";

    const char FEATUREQUESTION[] = ""
        "%s?\n";

    const char CERTAINQUESTION[] = ""
        "Is %s suitable?\n";

    const char GUESS_GOODBYE[] = ""
        "Enjoy listening.\n";

    const char GUESS_SURRENDER[] = ""
        "Sorry to hear. That is all i have. But finally, what is suitable for you?\n";

    const char GUESS_DIFFQUESTION[] = ""
        "What is %s as opposed to %s?\n";
}

#endif // TEXTS_H
