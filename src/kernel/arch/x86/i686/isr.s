# TODO: Macro-ize this
.global isr0

isr0:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr1

isr1:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr2

isr2:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr3

isr3:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr4

isr4:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr5

isr5:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr6

isr6:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr7

isr7:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr8

isr8:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr9

isr9:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr10

isr10:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr11

isr11:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr12

isr12:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr13

isr13:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr14

isr14:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr15

isr15:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr16

isr16:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr17

isr17:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr18

isr18:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr19

isr19:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr20

isr20:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr21

isr21:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr22

isr22:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr23

isr23:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr24

isr24:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr25

isr25:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr26

isr26:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr27

isr27:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr28

isr28:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr29

isr29:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr30

isr30:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.global isr31

isr31:
    cli             # Disable interrupts
    push 0              # Push the error code
    push 0              # Push the interrupt number
    jmp isr_common_stub

.extern isr_handler

isr_common_stub:
    sti
    iret
    pusha           # Save all registers

    mov %ax, %ds    # Set the data segment (lower 16-bits)
    push %eax       # Save the data segment descriptor

    mov %ax, 0x10    # Load the kernel data segment descriptor
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax

    call isr_handler

    # Restore the original state
    pop %eax
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax

    popa            # Restore all registers
    add %esp, 8     # Clean up the pushed error code and ISR number
    sti
    iret            # Return to the previous interrupt