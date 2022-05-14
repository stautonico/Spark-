/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#include "vga.h"
#include <kernel/kernel_libs/string.h>


VGA::VGATextTerminal::VGATextTerminal() {
    // Set the default colors
    set_colors(VGA::Color::WHITE, VGA::Color::BLACK);
    m_row = 0;
    m_column = 0;
    m_buffer = (uint16_t *) 0xB8000;

    clear();
}

void VGA::VGATextTerminal::set_fg_color(Color color) {
    m_fg_color = color;
}

void VGA::VGATextTerminal::set_bg_color(Color color) {
    m_bg_color = color;
}

void VGA::VGATextTerminal::set_colors(Color fg, Color bg) {
    set_fg_color(fg);
    set_bg_color(bg);
}

void VGA::VGATextTerminal::clear() {
    memset(m_buffer, 0, VGA_WIDTH * VGA_HEIGHT * 2);
}

void VGA::VGATextTerminal::putc(char c) {
    switch (c) {
        case '\n':
            m_column = 0;
            m_row++;
            break;
        case '\r':
            m_column = 0;
            break;
        default:
            m_buffer[m_row * VGA_WIDTH + m_column] = (m_fg_color << 8) | m_bg_color | c;
            m_column++;
            break;
    }

    if (m_column >= VGA_WIDTH) {
        m_column = 0;
        m_row++;
    }

    if (m_row >= VGA_HEIGHT) {
        m_row = 0;
    }
}

void VGA::VGATextTerminal::put_str(const char *str) {
    while (*str) {
        putc(*str++);
    }
}

void VGA::VGATextTerminal::put_number(uint32_t n, uint8_t base, const char *prefix) {
    char buf[16];
    itoa(n, buf, base);

    if (prefix) {
        put_str(prefix);
    }

    put_str(buf);

}

void VGA::VGATextTerminal::put_hex(uint32_t n) {
    put_number(n, 16, "0x");
}

void VGA::VGATextTerminal::put_dec(uint32_t n) {
    put_number(n, 10, "");
}

void VGA::VGATextTerminal::put_oct(uint32_t n) {
    put_number(n, 8, "0");
}

void VGA::VGATextTerminal::put_bin(uint32_t n) {
    char buf[33];
    itoa(n, buf, 2);
    put_str("0b");
    put_str(buf);
}

void VGA::VGATextTerminal::put_at(const char *str, size_t x, size_t y) {
    // Save our current position
    size_t saved_row = m_row;
    size_t saved_column = m_column;

    // Set the new position
    m_row = y;
    m_column = x;

    // If we have a single character, put it
    if (strlen(str) == 1) {
        putc(*str);
    } else {
        // Otherwise, put the string
        put_str(str);
    }
    // Restore the old position
    m_row = saved_row;
    m_column = saved_column;
}

void VGA::VGATextTerminal::putc_at(char c, size_t x, size_t y) {
    put_at(&c, x, y);
}

void VGA::VGATextTerminal::put_str_at(const char *str, size_t x, size_t y) {
    put_at(str, x, y);
}

void VGA::VGATextTerminal::put_hex_at(uint32_t n, size_t x, size_t y) {
    put_at("0x", x, y);
    put_at(itoa(n, nullptr, 16), x + 2, y);
}

void VGA::VGATextTerminal::put_dec_at(uint32_t n, size_t x, size_t y) {
    put_at(itoa(n, nullptr, 10), x, y);
}

void VGA::VGATextTerminal::put_oct_at(uint32_t n, size_t x, size_t y) {
    put_at("0", x, y);
    put_at(itoa(n, nullptr, 8), x + 1, y);
}

void VGA::VGATextTerminal::put_bin_at(uint32_t n, size_t x, size_t y) {
    put_at("0b", x, y);
    put_at(itoa(n, nullptr, 2), x + 2, y);
}