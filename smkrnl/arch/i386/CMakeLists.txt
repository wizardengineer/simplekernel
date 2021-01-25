set(CAN_USE_ASSEMBLER TRUE)
file(GLOB_RECURSE KERNEL_ASM_FILES "*.s")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set_source_files_properties(${KERNEL_ASM_FILES} PROPERTIES LANGUAGE ASM_NASM)

add_library(KERNEL_ASM_OBJECTS ${KENREL_ASM_FILES})

message("[+] ${kernel_asm_file} done compiling")
