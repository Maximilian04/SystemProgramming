/**
 * @file ValueOutFunction_t.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef VALUEOUTFUNCTION_T_H
#define VALUEOUTFUNCTION_T_H

#include <stddef.h>

#define ValueOutFunction_t_PARAMS size_t bufN, void const* valuePtr
typedef char const* (*ValueOutFunction_t)(ValueOutFunction_t_PARAMS);

#endif // VALUEOUTFUNCTION_T_H
