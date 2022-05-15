/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef SPARK_QEMU_H
#define SPARK_QEMU_H

#include <stdint.h>

/* From osdev
 * FW_CFG_PORT_SEL: 16-bit port.
 * You write a "selector" to this port to control which data will be
 * read when reading FW_CFG_PORT_DATA. More about selectors below.
 *
 * FW_CFG_PORT_DATA: 8-bit port.
 * You read one byte at a time of the file from this port,
 * after selecting a file by writing a value to FW_CFG_PORT_SEL.
 *
 * FW_CFG_PORT_DMA: 32-bit port. DMA transfers are done to this port.
 */


#define FW_CFG_PORT_SEL     0x510
#define FW_CFG_PORT_DATA    0x511
#define FW_CFG_PORT_DMA     0x514

#define FW_CFG_SIGNATURE    0x0000
#define FW_CFG_ID           0x0001
#define FW_CFG_FILE_DIR     0x0019

struct FirmwareConfigFile {
    uint32_t size;
    uint16_t selector;
    uint16_t reserved;
    char name[56];
};

bool is_qemu();


#endif // SPARK_QEMU_H