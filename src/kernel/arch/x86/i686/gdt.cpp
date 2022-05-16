/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include <kernel/arch/x86/gdt.h>


GDTEntry gdt[GDT_ENTRY_COUNT];
GDTPtr gdt_ptr;


GDTEntry GDTEntry::build_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    uint16_t base_low = (base & 0xFFFF);
    uint8_t base_mid = (base >> 16) & 0xFF;
    uint8_t base_high = (base >> 24) & 0xFF;

    uint16_t limit_low = (limit & 0xFFFF);
    uint8_t _flags = (limit >> 16) & 0xF; // ?

    _flags = flags & 0xF0;

    return {limit_low, base_low, base_mid, access, _flags, base_high};
}

void init_gdt() {
    gdt_ptr.limit = (sizeof(GDTEntry) * GDT_ENTRY_COUNT) - 1;
    gdt_ptr.base = (uint32_t) &gdt;

    gdt[0] = GDTEntry::build_entry(0, 0, 0, 0);                 // Null segment
    gdt[1] = GDTEntry::build_entry(0, 0xFFFFFFFF, 0x9A, 0xCF);  // Code segment
    gdt[2] = GDTEntry::build_entry(0, 0xFFFFFFFF, 0x92, 0xCF);  // Data segment
    gdt[3] = GDTEntry::build_entry(0, 0xFFFFFFFF, 0xFA, 0xCF);  // User mode code segment
    gdt[4] = GDTEntry::build_entry(0, 0xFFFFFFFF, 0xF2, 0xCF);  // User mode data segment

    gdt_flush((uint32_t) &gdt_ptr);
}