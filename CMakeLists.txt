cmake_minimum_required(VERSION 3.16.3)

# setting assembly code
enable_language(C ASM_NASM)
if(CMAKE_ASM_COMPILER_LOADED)
    set(CAN_USE_ASSEMBLER TRUE)
    file(GLOBAL_RECURSE CMAKE_ASM_FILES "${CRT_DIR}/smkrnl/arch/i386/*.s")
endif(CMAKE_ASM_COMPILER_LOADED)

project(simplekernel)

include(libc/functions.cmake)

set(CMAKE_C_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

# setting current dir for easy use
set(CRT_DIR ${CMAKE_CURRENT_LIST_DIR})


# setting link.ld
set(CMAKE_LINKER_FILE "${CRT_DIR}/smkrnl/arch/i386/linker.ld")
set(CMAKE_LINKER_FLAGS " -T ${CMAKE_LINKER_FILE} -melf_i386")


# setting kenrel c code
file(GLOBAL_RECURSE KENREL_ARCH_C_FILES "${CRT_DIR}/smkrnl/arch/i386/*.c")
file(GLOBAL_RECURSE KERNEL_C_FILES "${CRT_DIR}/smkrnl/*.c")
set(CMAKE_ALL_KC_FILES "${KERNEL_C_FILES} ${KENREL_ARCH_C_FILES}")

add_library(kernel_main OBJECT ${KENREL_C_FILES})
add_library(kernel_arch_files OBJECT ${KERNEL_ARCH_C_FILES})

target_link_libraries(kernel_arch_files PUBLIC kernel_main)

add_library(asm_files OBJECT ${CMAKE_ASM_FILES})

target_link_libraries(asm_files PUBLIC kernel_main)
