/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include "panic.h"
#include <kernel/drivers/vga.h>
#include <kernel/debug.h>
#include <kernel/drivers/vga.h>
#include <kernel/kernel_libs/string.h>

[[noreturn]] void panic(const char *msg) {
    Kernel::Debug::panicf("%s\n", msg);
    vga_text_terminal.set_fg_color(VGA::Color::RED);
    // TODO: Replace this with some printf formatting
    vga_text_terminal.put_str(strcat("Kernel Panic: ", msg));

    // TODO: Halt the CPU
    asm volatile("cli");
    while (true) {};
}