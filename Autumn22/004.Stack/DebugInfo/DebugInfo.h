/**
 * @file DebugInfo.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#define DEBUGINFO_CTOR_ARGS_H     const char* objName, const char* ctorCallFunc, const char* ctorCallFile, const int ctorCallLine
#define DEBUGINFO_CTOR_ARGS_R(objName)        objName,      __PRETTY_FUNCTION__,                 __FILE__,               __LINE__

struct DebugInfo {
    const char* objName;
    const char* ctorCallFunc;
    const char* ctorCallFile;
    int         ctorCallLine;
};

#endif // DEBUGINFO_H
