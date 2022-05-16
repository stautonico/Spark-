#include <kernel/debug.h>
#include <kernel/drivers/vga.h>
#include <kernel/arch/x86/power.h>
#include <kernel/panic.h>
#include <kernel/arch/x86/gdt.h>
#include <kernel/arch/x86/idt.h>


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#ifdef __cplusplus
extern "C"
#endif
void kmain(void) {
    // http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
    // http://www.jamesmolloy.co.uk/tutorial_html/
    init_gdt();
    init_idt();

//    asm volatile("int $0x0");
//    asm volatile("int $0x4");

    terminal.put_str("Hello, world!\n");

    terminal.set_colors(VGA::Color::LIGHT_RED, VGA::Color::BLACK);

    terminal.put_str("This is my next str\n");

//    terminal.move_cursor()

//    Kernel::Debug::debugf("Hello from spark++ via serial on COM1!\n");

    panic("pretend something bad happened");

    shutdown();
}