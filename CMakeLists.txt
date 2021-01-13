cmake_minimum_required(VERSION 3.16.3)

include(libc)

project(cmake_testing VERSION 1.0 LANGUAGE C)

set(CMAKE_C_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c")

# setting link.ld
set(CMAKE_LINKER "${CMAKE_CURRENT_LIST_DIR}/smkrnl/arch/i386/linker.ld")

set(CMAKE_LINKER_FLAGS " T ${CMAKE_LINKER} -melf_i386")
