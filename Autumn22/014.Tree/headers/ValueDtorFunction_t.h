/**
 * @file ValueDtorFunction_t.h
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef VALUEDTORFUNCTION_T_H
#define VALUEDTORFUNCTION_T_H

#include <stddef.h>

#define ValueDtorFunction_t_PARAMS void* valuePtr
typedef int (*ValueDtorFunction_t)(ValueDtorFunction_t_PARAMS);

#endif // VALUEDTORFUNCTION_T_H
