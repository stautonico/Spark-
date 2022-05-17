/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_GDT_H
#define SPARK_GDT_H

#include <stdint.h>

#define GDT_ENTRY_COUNT 5


// Assembly functions
extern "C" void gdt_flush(uint32_t);

#endif // SPARK_GDT_H

