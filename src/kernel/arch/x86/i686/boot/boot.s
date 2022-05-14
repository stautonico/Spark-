# Multiboot loader
.set ALIGN, 1<<0 # Align module pages to 1<<0 (4K)
.set MEMINFO, 1<<1 # Include memory information in the header
.set FLAGS, ALIGN | MEMINFO # Flags to pass to the multiboot
.set MAGIC, 0x1BADB002 # Multiboot magic number
.set CHECKSUM, -(MAGIC + FLAGS) # Checksum of the magic and flags

.section .multiboot
.align 4 # Align to 4 bytes
.long MAGIC # Multiboot magic number
.long FLAGS # Multiboot flags
.long CHECKSUM # Multiboot checksum

# Reserve 16k for the stack
.section .bootstrap_stack
stack_bottom:
.skip 16384 # 16k stack
stack_top:


.section .text

.global __idt_default_handler
.type __idt_default_handler, @function
__idt_default_handler:
    pushal # Save registers
    mov $0x20, %al # Send an interrupt to the kernel
    mov $0x20, %dx # Send an interrupt to the kernel
    out %al, %dx # Send an interrupt to the kernel
    popal # Restore registers
    iretl # Return from interrupt

.global _set_gdtr
.type _set_gdtr, @function
_set_gdtr:
    push %ebp # Save ebp
    movl %esp, %ebp # Set ebp to esp

    lgdt 0x800 # Load the gdt
    movl %ebp, %esp # Restore esp
    pop %ebp # Restore ebp
    ret # Return

.global _set_idtr
.type _set_idtr, @function
_set_idtr:
    push %ebp # Save ebp
    movl %esp, %ebp # Set ebp to esp

    lidt 0x10F0 # Load the idt

    movl %ebp, %esp # Restore esp
    pop %ebp # Restore ebp
    ret # Return

.global _reload_segments
.type _reload_segments, @function
_reload_segments:
    push %ebp # Save ebp
    movl %esp, %ebp # Set ebp to esp

    push %eax # Save eax
    mov $0x10, %ax # Set the selector to the kernel code segment
    mov %ax, %ds # Set the kernel code segment
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    pop %eax # Restore eax

    ljmp $0x8, $me # Jump to the kernel

me:
    movl %ebp, %esp # Restore esp
    pop %ebp # Restore ebp
    ret # Return

# Main start label (called by the bootloader)
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp # Set esp to the stack
    mov $0x1337, %eax # Set eax to a magic number

    call kmain # Call the kernel

    cli # Disable interrupts
    hlt # Halt (should never reach this point)

.Lhang:
    jmp .Lhang


.size _start, . - _start
