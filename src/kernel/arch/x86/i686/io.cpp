/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#include <kernel/arch/x86/io.h>

void outb(uint16_t port, uint8_t val) {
    // TODO: Check the architecture and use the appropriate assembly instruction
#ifdef __i386__
    asm volatile("OUT %1, %0" : : "dN" (port), "a" (val));
#elif __x86_64__
    asm volatile("outb %0, %1" : : "a" (val), "Nd" (port));
#endif
}
uint8_t inb(uint16_t port) {
    uint8_t ret;
#ifdef __i386__
    asm volatile("IN %1, %0" : "=a" (ret) : "dN" (port));
#elif __x86_64__
    asm volatile("inb %1, %0" : "=a" (ret) : "Nd" (port));
#endif
    return ret;
}

void outw(uint16_t port, uint16_t val) {
#ifdef __i386
    asm volatile("OUT %1, %0" : : "dN" (port), "a" (val));
#elif __x86_64__
    asm volatile("outw %0, %1" : : "a" (val), "Nd" (port));
#endif
}

uint16_t inw(uint16_t port) {
    uint16_t ret;
#ifdef __i386__
    asm volatile("IN %1, %0" : "=a" (ret) : "dN" (port));
#elif __x86_64__
    asm volatile("inw %1, %0" : "=a" (ret) : "Nd" (port));
#endif
    return ret;
}