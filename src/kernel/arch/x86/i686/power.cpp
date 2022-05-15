/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifdef __i386__

#include <kernel/arch/x86/power.h>
#include <kernel/arch/x86/io.h>

#else
#error "Unsupported architecture"
#endif


void shutdown() {
    // TODO: Check what we're running and call the appropriate shutdown function
    //       for the platform.
    shutdown_qemu();
}

void shutdown_qemu() {
    outw(0x604, 0x2000);
}