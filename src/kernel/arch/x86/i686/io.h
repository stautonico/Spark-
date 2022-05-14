/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef SPARK_IO_H
#define SPARK_IO_H
#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif // SPARK_IO_H