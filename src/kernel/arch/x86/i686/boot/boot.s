# Multiboot bootloader
.set MULTIBOOT_PAGE_ALIGN, 1<<0 # Align our pages to 4k
.set MULTIBOOT_MEM_INFO, 1<<1 # Include memory information in our header
.set MULTIBOOT_FLAGS, (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO) # Flags to pass to the multiboot
.set MULTIBOOT_MAGIC, 0x1BADB002 # Multiboot magic number
.set MULTIBOOT_CHECKSUM, -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS) # Checksum of the magic and flags

.global mboot # Pass multiboot header to C/C++
.extern code, bss, end

mboot:
    .long MULTIBOOT_MAGIC # Make multiboot available to grub
    .long MULTIBOOT_FLAGS
    .long MULTIBOOT_CHECKSUM

    .long mboot # Add the location of this label
    .long code # Start of the kernel (.text or 'code' section)
    .long bss # End of the kernel '.data' section
    .long end # End of the kernel
    .long start

.global start # Entry point
.extern kmain # Use the kernel's main funcion (kmain)

start:
    push %ebx # Load the multiboot header location

    # START KERNEL
    cli # Disable interrupts
    call kmain # Call the kernel
    # We should never pass this point
    # but if we do, just infinate loop
endlessloop:
    jmp endlessloop
