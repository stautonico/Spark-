## This cmake file was (mostly) shamelessly copied from the https://github.com/zhmu/ananas/.
## Thanks zhmu, you rock! (I can't write cmake to save my life...)
#project(kernel ASM C CXX)
#cmake_minimum_required(VERSION 3.20)
#
#set(CMAKE_TOOLCHAIN_FILE ../CMake/toolchain.cmake)
#
#set(COMMON_FLAGS "")
#set(COMMON_FLAGS "${COMMON_FLAGS} -fno-builtin -nostdlib -nostdinc")
#set(COMMON_FLAGS "${COMMON_FLAGS} -I./include")
#set(COMMON_FLAGS "${COMMON_FLAGS}")
#
## Machine specific flags
#set(COMMON_FLAGS "${COMMON_FLAGS} -m32 -march=i686")
#set(COMMON_FLAGS "${COMMON_FLAGS} -mno-red-zone -mno-sse -fno-stack-protector")
#
## Include debug flags
#set(COMMON_FLAGS "${COMMON_FLAGS} -g -ggdb")
#
#set(KERNEL_BIN ${TARGET_ARCH}-kernel.bin)
#
#set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/arch/${TARGET_ARCH}/link.ld)
#set(GRUB_CFG ${CMAKE_CURRENT_SOURCE_DIR}/arch/${TARGET_ARCH}/iso/boot/grub/grub.cfg)
#
#set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32-i686")
#
#set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -mno-red-zone -mno-sse -ffreestanding -nostdlib -fno-pie -fno-pic -no-pie")
#set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${CMAKE_C_FLAGS} -mno-red-zone -mno-sse -ffreestanding -nostdlib -fno-pie -fno-pic -no-pie")
#set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")
#
#enable_language(ASM_NASM)
#
#file(GLOB KERNEL_SRCS *.c)
##file(GLOB C_MODULES src/impl/x86_64/*.c)
#file(GLOB BOOT_ASM_MODULES arch/${TARGET_ARCH}/loader/*.s)
#
#message(STATUS "Building kernel... (${TARGET_ARCH} ${KERNEL_SRCS} ${BOOT_ASM_MODULES})")
#
#add_executable(${KERNEL_BIN}
#        ${KERNEL_SRCS}
#        ${C_MODULES}
#        ${BOOT_ASM_MODULES}
#        )
#
#set(CMAKE_LINKER_FLAGS "-n -o -T ${LINKER_SCRIPT} -ffreestanding -nostdlib -fno-pie -fno-pic -no-pie -lgcc")
#set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_C_COMPILER> ${CMAKE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
#
#set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
##set(CMAKE_CXX_LINK_FLAGS "-b i686-elf -T ${CMAKE_CURRENT_SOURCE_DIR}/conf/ld.amd64 -nostdlib -nodefaultlibs")
#
#set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS "-n -T ${LINKER_SCRIPT}")
#
#message(STATUS "KERNEL_BIN: ${KERNEL_BIN} (${TARGET_ARCH})")
#
##add_custom_command(TARGET ${KERNEL_BIN} POST_BUILD
##        COMMAND mkdir -p build/${TARGET_ARCH}/boot/grub
##        COMMAND cp ${KERNEL_BIN} build/${TARGET_ARCH}/boot/${KERNEL_BIN}
##        COMMAND cp ${GRUB_CFG} build/${TARGET_ARCH}/boot/grub
##        COMMAND grub-mkrescue -o kernel.iso build/${TARGET_ARCH}/
##        COMMAND rm -r build/
##        )
#
##function(build_object dest src opts)
##    string(REPLACE " " ";" flags ${CMAKE_CXX_FLAGS})
##    add_custom_command(
##            OUTPUT ${dest}
##            COMMAND ${CMAKE_CXX_COMPILER} ${flags} ${opts} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${dest} ${CMAKE_CURRENT_SOURCE_DIR}/${src} ${opts}
##    )
##endfunction()
##
##function(add_sources)
##    foreach(_s IN ITEMS ${ARGV})
##        get_filename_component(_a "${_s}" ABSOLUTE)
##        set_property(GLOBAL APPEND PROPERTY SourceList "${_a}")
##    endforeach()
##endfunction()
##
### From here, do add_subdirectory(...)
##add_subdirectory(arch)
##
##get_property(SOURCES GLOBAL PROPERTY SourceList)
##set(SOURCES ${SOURCES} include/_gen/syscalls.h include/_gen/syscalls.inc.h)
###add_executable(kernel_elf arch/amd64/prelude.S ${SOURCES} arch/amd64/postlude.S )
##add_executable(kernel_elf ${SOURCES} main.c)
##set_target_properties(kernel_elf PROPERTIES LINKER_LANGUAGE C)
##set_target_properties(kernel_elf PROPERTIES OUTPUT_NAME "kernel.elf")
##
##add_custom_command(
##        OUTPUT kernel.bin
##        COMMENT "Converting kernel ELF to binary"
##        DEPENDS kernel_elf
##        COMMAND objcopy -O binary $<TARGET_FILE:kernel_elf> ${CMAKE_CURRENT_BINARY_DIR}/kernel.bin
##)
##add_custom_target(kernel_bin DEPENDS kernel.bin)
##
### add a custom target that combines the multiboot stub to get a bootable kernel
### XXX this will only work on unix-like systems
##add_custom_command(
##        OUTPUT kernel
##        COMMENT "Merging kernel binary with multiboot loader"
##        DEPENDS multiboot kernel.bin
##        COMMAND cat $<TARGET_FILE:multiboot> ${CMAKE_CURRENT_BINARY_DIR}/kernel.bin > ${CMAKE_CURRENT_BINARY_DIR}/kernel
##)
##
##add_custom_target(kernel_mb ALL DEPENDS kernel)
##install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kernel DESTINATION .)
##
### prepare our include directories: we make a symlink to avoid unnecessary
### rebuilds
##add_custom_target(kernel_md_param_h ALL
##        COMMAND ${CMAKE_COMMAND} -E create_symlink
##        ${CMAKE_CURRENT_SOURCE_DIR}/include/kernel/amd64
##        ${CMAKE_CURRENT_BINARY_DIR}/include/kernel-md
##        )
##add_dependencies(kernel_elf kernel_md_param_h)
##add_custom_target(machine_types_h ALL
##        COMMAND ${CMAKE_COMMAND} -E create_symlink
##        ${CMAKE_CURRENT_SOURCE_DIR}/../kernel-interface/ananas/amd64
##        ${CMAKE_CURRENT_BINARY_DIR}/include/machine
##        )
##add_dependencies(kernel_elf machine_types_h)
##
### generate syscalls.h from the kern's syscalls.in - we don't care about
### anything else so just write to /dev/null there
##set(KERN_PATH ${CMAKE_SOURCE_DIR}/kern)
##add_custom_command(
##        OUTPUT include/_gen/syscalls.h
##        COMMAND ${KERN_PATH}/gen_syscalls.sh ${KERN_PATH}/syscalls.in /dev/null ${CMAKE_BINARY_DIR}/include/_gen/syscalls.h /dev/null
##        DEPENDS ${KERN_PATH}/syscalls.in
##)
##add_custom_target(syscall_gen DEPENDS include/_gen/syscalls.h)
##add_dependencies(kernel_elf syscall_gen)
##
### generate syscalls.inc.h like before. the .h extension is cheating, but this
### avoids CMake trying to build it
##add_custom_command(
##        OUTPUT include/_gen/syscalls.inc.h
##        COMMAND ${KERN_PATH}/gen_syscalls.sh ${KERN_PATH}/syscalls.in /dev/null /dev/null ${CMAKE_BINARY_DIR}/include/_gen/syscalls.inc.h
##        DEPENDS ${KERN_PATH}/syscalls.in
##)
#


cmake_minimum_required(VERSION 3.20)
project(spark-kernel)

## Setup cross-compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ${TARGET_ARCH})

ENABLE_LANGUAGE(ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra")


## A simple lib to test C compilation and linking
#add_library(mylib mylib.c)

# TODO: Look how serenity does this
# or do a add_subdirectory(drivers) and add_subdirectory(arch)

set(KERNEL_SOURCES drivers/serial.cpp arch/i686/io.cpp kernel_libs/printf.cpp kernel_libs/printf.h kernel_libs/string.cpp kernel_libs/string.cpp kernel_libs/string.h)

## Building the kernel binary
add_executable(spark.bin ${CMAKE_CURRENT_SOURCE_DIR}/arch/${TARGET_ARCH}/boot/boot.s kmain.cpp ${KERNEL_SOURCES})
set_target_properties(spark.bin PROPERTIES LINK_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/arch/${TARGET_ARCH}/link.ld -ffreestanding -O2 -nostdlib -lgcc")

target_include_directories(spark.bin PRIVATE ${CMAKE_SOURCE_DIR}/src/)