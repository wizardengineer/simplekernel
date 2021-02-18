symbol-file kernel.elf
target remote 127.0.0.1:1234
b _start
c
