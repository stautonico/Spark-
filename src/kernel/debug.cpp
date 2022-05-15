/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include "debug.h"
#include <stdarg.h>
#include <kernel/drivers/serial.h>
#include <kernel/kernel_libs/printf.h>
#include <kernel/kernel_libs/string.h>

// TODO: Add color support
void Kernel::Debug::debugf(const char *fmt, ...) {
    fmt = strcat("[ DEBUG ] ", fmt);
    va_list ap;
    va_start(ap, fmt);
    vsprintf(nullptr, serial::write_serial, fmt, ap);
    va_end(ap);
}

void Kernel::Debug::warnf(const char *fmt, ...) {
    fmt = strcat("[ WARN ] ", fmt);
    va_list(ap);
    va_start(ap, fmt);
    vsprintf(nullptr, serial::write_serial, fmt, ap);
    va_end(ap);
}

void Kernel::Debug::errorf(const char *fmt, ...) {
    fmt = strcat("[ ERROR ] ", fmt);
    va_list(ap);
    va_start(ap, fmt);
    vsprintf(nullptr, serial::write_serial, fmt, ap);
    va_end(ap);
}

void Kernel::Debug::panicf(const char *fmt, ...) {
    fmt = strcat("[ PANIC ] ", fmt);
    va_list(ap);
    va_start(ap, fmt);
    vsprintf(nullptr, serial::write_serial, fmt, ap);
    va_end(ap);
}