#include <kernel/drivers/vga.h>
#include <kernel/debug.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#ifdef __cplusplus
extern "C"
#endif
void kmain(struct multiboot *multiboot_ptr) {
    // TODO: Re-write the GDT and IDT
    http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
    VGA::VGATextTerminal terminal;
    terminal.put_str("Hello kernel!");
    Kernel::Debug::debugf("Hello kernel!");
    // http://www.jamesmolloy.co.uk/tutorial_html/
}