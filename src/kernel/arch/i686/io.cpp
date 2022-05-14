/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#include "io.h"

void outb(uint16_t port, uint8_t val) {
    // TODO: Check the architecture and use the appropriate assembly instruction
#ifdef __i386__
    asm volatile("OUT %1, %0" : : "dN" (port), "a" (val));
#elifdef __x86_64__
    asm volatile("outb %0, %1" : : "a" (val), "Nd" (port));
#endif
}
uint8_t inb(uint16_t port) {
    uint8_t ret;
#ifdef __i386__
    asm volatile("IN %1, %0" : "=a" (ret) : "dN" (port));
#elifdef __x86_64__
    asm volatile("inb %1, %0" : "=a" (ret) : "Nd" (port));
#endif
    return ret;
}