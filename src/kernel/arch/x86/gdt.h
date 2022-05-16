/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_GDT_H
#define SPARK_GDT_H

#include <stdint.h>

#define GDT_ENTRY_COUNT 5

class __attribute__((__packed__)) GDTEntry {
public:
    GDTEntry() = default;

    GDTEntry(uint16_t limit_low, uint16_t base_low, uint8_t base_middle, uint8_t access, uint8_t flags,
             uint8_t base_high) : m_limit_low(limit_low), m_base_low(base_low), m_base_middle(base_middle),
                                  m_access(access), m_flags(flags), m_base_high(base_high) {};

    static GDTEntry build_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

    [[nodiscard]] uint16_t limit_low() const { return m_limit_low; }

    [[nodiscard]] uint16_t base_low() const { return m_base_low; }

    [[nodiscard]] uint8_t base_middle() const { return m_base_middle; }

    [[nodiscard]] uint8_t access() const { return m_access; }

    [[nodiscard]] uint8_t flags() const { return m_flags; }

    [[nodiscard]] uint8_t base_high() const { return m_base_high; }

private:
    uint16_t m_limit_low{0};
    uint16_t m_base_low{0};
    uint8_t m_base_middle{0};
    uint8_t m_access{0};
    uint8_t m_flags{0}; // Also called 'granularity'
    uint8_t m_base_high{0};
};

struct GDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((__packed__));

void init_gdt();

// Assembly functions
extern "C" void gdt_flush(uint32_t);

#endif // SPARK_GDT_H

