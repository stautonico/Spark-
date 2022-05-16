# TODO: Add the proper files to the sources depending on the architecture
set(KERNEL_SOURCES
        ${KERNEL_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/io.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/power.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/qemu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/gdt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/gdt.s
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/idt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/idt.s
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/isr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/isr.s

        PARENT_SCOPE
        )