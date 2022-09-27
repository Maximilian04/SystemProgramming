/**
 * @file loggerIncludeDefines.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Defines for logger
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LOGGERINCLUDEDEFINES_H
#define LOGGERINCLUDEDEFINES_H

#define LOGFUNCHEAD_PARAMS_H const char* funcName, const char* fileName, const int lineN
#define LOGFUNCHEAD_PARAMS_R  __PRETTY_FUNCTION__,             __FILE__,        __LINE__
#define LOGFUNCHEAD_PARAMS               funcName,             fileName,           lineN

#endif // LOGGERINCLUDEDEFINES_H
