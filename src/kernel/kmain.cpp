#include <kernel/debug.h>
#include <kernel/drivers/vga.h>


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

extern "C" void kmain(void)
{
    VGA::VGATextTerminal terminal;

    terminal.put_str("Hello, world!\n");

    terminal.set_colors(VGA::Color::LIGHT_RED, VGA::Color::BLACK);

    terminal.put_str("This is my next str\n");

    terminal.put_hex(0xDEADBEEF);
    terminal.putc('\n');
    terminal.put_dec(8008135);
    terminal.putc('\n');
    terminal.put_oct(0664);
    terminal.putc('\n');
    terminal.put_bin(0xDEADBEEF);

    terminal.set_colors(VGA::Color::LIGHT_GREEN, VGA::Color::BLACK);

    terminal.set_colors(VGA::Color::LIGHT_BLUE, VGA::Color::BLACK);
    terminal.put_str("This will continue from the last position");

    terminal.set_colors(VGA::Color::LIGHT_RED, VGA::Color::BLACK);

    terminal.putc_at('B', 10, 10);

    terminal.put_str_at("Moved", 11, 11);

    terminal.set_colors(VGA::Color::LIGHT_GREEN, VGA::Color::BLACK);

    terminal.put_hex_at(0xDEADBEEF, 10, 12);

    terminal.put_dec_at(8008135, 10, 13);

    terminal.put_oct_at(0664, 10, 14);

    terminal.put_bin_at(0xDEADBEEF, 10, 15);

    terminal.set_colors(VGA::Color::LIGHT_BLUE, VGA::Color::BLACK);

    terminal.put_str("This will continue from the last position");


    Kernel::Debug::debugf("Hello from spark++ via serial on COM1!\n");
}