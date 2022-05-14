/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_PRINTF_H
#define SPARK_PRINTF_H

#include <stdarg.h>
#include <stdint.h>

int is_format_letter(char c);

void vsprintf(char *str, void (*putchar)(char), const char *format, va_list arg);

void vsprintf_helper(char *str, void (*putchar)(char), const char *format, uint32_t *pos, va_list arg);


#endif // SPARK_PRINTF_H