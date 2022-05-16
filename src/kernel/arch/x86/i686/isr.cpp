/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */
#include <kernel/arch/x86/isr.h>
#include <kernel/debug.h>

extern "C" void isr_handler(registers_t regs) {
    Kernel::Debug::debugf("Interrupt received: %d", regs.int_no);
}