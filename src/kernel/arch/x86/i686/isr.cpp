/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#include <kernel/arch/x86/isr.h>
#include <kernel/debug.h>
#include <kernel/drivers/vga.h>

extern "C" void isr_handler(registers_t regs) {
//    Kernel::Debug::debugf("[isr] Interrupt modd occured!\n", regs.int_no);
    VGA::VGATextTerminal display;
    display.move_cursor(20, 5);
    display.set_colors(VGA::Color::WHITE, VGA::Color::BLACK);
    display.put_str("Interrupt occurred: ");
    display.put_dec(regs.int_no);
    display.putc('\n');
//    Kernel::Debug::debugf("Interrupt received: %d", regs.int_no);
}