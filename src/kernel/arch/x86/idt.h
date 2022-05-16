/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_IDT_H
#define SPARK_IDT_H

#include <stdint.h>

#define IDT_ENTRY_COUNT 256

class __attribute__((__packed__)) IDTEntry {
public:
    IDTEntry() = default;

    IDTEntry(uint16_t base_low, uint16_t selector, uint8_t flags, uint16_t base_high) : m_base_low(base_low),
                                                                                        m_selector(selector),
                                                                                        m_flags(flags),
                                                                                        m_base_high(base_high) {};

    static IDTEntry build_entry(uint32_t base, uint16_t selector, uint8_t flags);

    [[nodiscard]] uint16_t base_low() const { return m_base_low; }

    [[nodiscard]] uint16_t selector() const { return m_selector; }

    [[nodiscard]] uint8_t flags() const { return m_flags; }

    [[nodiscard]] uint16_t base_high() const { return m_base_high; }

private:
    uint16_t m_base_low{0}; // Lower 16 bits of the address to jump to when this interrupt fires.
    uint16_t m_selector{0}; // Kernel segment selector.
    uint8_t m_always0{0}; // This must always be zero. (wtf?)
    uint8_t m_flags{0}; // Type of interrupt;
    uint16_t m_base_high{0}; // Upper 16 bits of the address to jump to.

    /*
     * Bitfields for flags:
     * 0101 or 0x5: Task Gate, note that in this case, the Offset value is unused and should be set to zero.
     * 0110 or 0x6: 16-bit Interrupt Gate
     * 0111 or 0x7: 16-bit Trap Gate
     * 1110 or 0xE: 32-bit Interrupt Gate
     * 1111 or 0xF: 32-bit Trap Gate
     * https://wiki.osdev.org/Interrupt_Descriptor_Table
     */
};

struct IDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((__packed__));

void init_idt();

// Assembly functions
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

#endif // SPARK_IDT_H

