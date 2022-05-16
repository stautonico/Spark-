/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include <kernel/arch/x86/idt.h>
#include <kernel/kernel_libs/string.h>

IDTEntry idt[IDT_ENTRY_COUNT];
IDTPtr idt_ptr;

IDTEntry IDTEntry::build_entry(uint32_t base, uint16_t selector, uint8_t flags) {
    uint16_t base_low = base & 0xFFFF;
    uint16_t base_high = (base >> 16) & 0xFFFF;

    return {base_low, selector, flags, base_high};
}

void init_idt() {
    idt_ptr.limit = sizeof(IDTEntry) * IDT_ENTRY_COUNT - 1;
    idt_ptr.base = (uint32_t) &idt;

    memset(&idt, 0, sizeof(IDTEntry) * IDT_ENTRY_COUNT);


    // Set the default interrupt handlers
    idt[0] = IDTEntry::build_entry((uint32_t)isr0, 0x08, 0x8E);
    idt[1] = IDTEntry::build_entry((uint32_t)isr1, 0x08, 0x8E);
    idt[2] = IDTEntry::build_entry((uint32_t)isr2, 0x08, 0x8E);
    idt[3] = IDTEntry::build_entry((uint32_t)isr3, 0x08, 0x8E);
    idt[4] = IDTEntry::build_entry((uint32_t)isr4, 0x08, 0x8E);
    idt[5] = IDTEntry::build_entry((uint32_t)isr5, 0x08, 0x8E);
    idt[6] = IDTEntry::build_entry((uint32_t)isr6, 0x08, 0x8E);
    idt[7] = IDTEntry::build_entry((uint32_t)isr7, 0x08, 0x8E);
    idt[8] = IDTEntry::build_entry((uint32_t)isr8, 0x08, 0x8E);
    idt[9] = IDTEntry::build_entry((uint32_t)isr9, 0x08, 0x8E);
    idt[10] = IDTEntry::build_entry((uint32_t)isr10, 0x08, 0x8E);
    idt[11] = IDTEntry::build_entry((uint32_t)isr11, 0x08, 0x8E);
    idt[12] = IDTEntry::build_entry((uint32_t)isr12, 0x08, 0x8E);
    idt[13] = IDTEntry::build_entry((uint32_t)isr13, 0x08, 0x8E);
    idt[14] = IDTEntry::build_entry((uint32_t)isr14, 0x08, 0x8E);
    idt[15] = IDTEntry::build_entry((uint32_t)isr15, 0x08, 0x8E);
    idt[16] = IDTEntry::build_entry((uint32_t)isr16, 0x08, 0x8E);
    idt[17] = IDTEntry::build_entry((uint32_t)isr17, 0x08, 0x8E);
    idt[18] = IDTEntry::build_entry((uint32_t)isr18, 0x08, 0x8E);
    idt[19] = IDTEntry::build_entry((uint32_t)isr19, 0x08, 0x8E);
    idt[20] = IDTEntry::build_entry((uint32_t)isr20, 0x08, 0x8E);
    idt[21] = IDTEntry::build_entry((uint32_t)isr21, 0x08, 0x8E);
    idt[22] = IDTEntry::build_entry((uint32_t)isr22, 0x08, 0x8E);
    idt[23] = IDTEntry::build_entry((uint32_t)isr23, 0x08, 0x8E);
    idt[24] = IDTEntry::build_entry((uint32_t)isr24, 0x08, 0x8E);
    idt[25] = IDTEntry::build_entry((uint32_t)isr25, 0x08, 0x8E);
    idt[26] = IDTEntry::build_entry((uint32_t)isr26, 0x08, 0x8E);
    idt[27] = IDTEntry::build_entry((uint32_t)isr27, 0x08, 0x8E);
    idt[28] = IDTEntry::build_entry((uint32_t)isr28, 0x08, 0x8E);
    idt[29] = IDTEntry::build_entry((uint32_t)isr29, 0x08, 0x8E);
    idt[30] = IDTEntry::build_entry((uint32_t)isr30, 0x08, 0x8E);
    idt[31] = IDTEntry::build_entry((uint32_t)isr31, 0x08, 0x8E);


}