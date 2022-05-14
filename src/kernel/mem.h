/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_MEM_H
#define SPARK_MEM_H

#include <stddef.h>

namespace Kernel {
void *kmalloc(size_t size);
void kfree(void *ptr);
}

#endif // SPARK_MEM_H