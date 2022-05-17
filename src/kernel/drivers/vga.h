/*
 Copyright (c) 2022, Steve Tautonico.

 SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SPARK_VGA_H
#define SPARK_VGA_H

#include <stdint.h>
#include <stddef.h>


namespace VGA {
    enum Color {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GREY = 7,
        DARK_GREY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        LIGHT_BROWN = 14,
        WHITE = 15,
    };


    class VGATextTerminal {
        static const size_t VGA_WIDTH = 80;
        static const size_t VGA_HEIGHT = 25;


    public:
        VGATextTerminal();

        void set_colors(Color fg, Color bg);

        void set_fg_color(Color color);

        void set_bg_color(Color color);

        void clear();

        void putc(char c);

        void put_str(const char *str);

        void put_hex(uint32_t n);

        void put_dec(uint32_t n);

        void put_oct(uint32_t n);

        void put_bin(uint32_t n);

        void putc_at(char c, size_t x, size_t y);

        void put_str_at(const char *str, size_t x, size_t y);

        void put_hex_at(uint32_t n, size_t x, size_t y);

        void put_dec_at(uint32_t n, size_t x, size_t y);

        void put_oct_at(uint32_t n, size_t x, size_t y);

        void put_bin_at(uint32_t n, size_t x, size_t y);

        // TODO: Implement 'hardware' cursor
        void move_cursor(size_t x, size_t y);

        bool set_cursor(size_t x, size_t y);

    private:
        uint16_t *m_buffer;
        size_t m_row;
        size_t m_column;
        uint8_t m_fg_color{};
        uint8_t m_bg_color{};

        uint16_t get_vga_entry(char c, uint8_t color);

        void scroll();

        void move_cursor();

        void put_number(uint32_t n, uint8_t base, const char *prefix = nullptr);

        void put_at(const char *str, size_t x, size_t y);
    };
}; // namespace VGA

extern VGA::VGATextTerminal vga_text_terminal;

#endif // SPARK_VGA_H