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
