/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_SERIAL_H
#define SPARK_SERIAL_H

#define COM1  0x3F8
#define COM2  0x2F8
#define COM3  0x3E8
#define COM4  0x2E8
#define COM5  0x5F8
#define COM6  0x4F8
#define COM7  0x5E8
#define COM8  0x4E8

namespace serial {

void serial_init();

void write_serial(char a);

int is_transmit_empty();

// TODO: Put this in a "debug" file or namespace
void qemu_printf(const char *fmt, ...);

} // namespace serial

#endif // SPARK_SERIAL_H