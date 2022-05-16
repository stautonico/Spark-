.global idt_flush

idt_flush:
    mov %eax, 4(%esp)
    lidt (%eax)
    ret