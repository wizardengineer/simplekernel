#include <kernel/isr.h>
#include <kernel/idt.h>
#include <io/serial_port.h>

/* AMD manual Exceptions and Interrupts */
const char *exception_messages[IDT_FIRST_32_GATES] =
{
  "Division By Zero Exception",
  "Debug Exception",
  "Non Maskable Interrupt Exception",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid Opcode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coprocessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Alignment Check Exception (486+)",
  "Machine Check Exception (Pentium/586+)",
  "SIMD Floating-Point", // 19
  "Reserved Exceptions",
  "Control-Protection Exception",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Reserved Exceptions",
  "Hypervisor Injection Exception",
  "VMM Communication Exception",
  "Security Exception",
  "Reserved Exceptions"
};

void fault_handler(regs registers)
{
#if defined(__KERN_DEBUG)
  serial_print("Fault_handler started\n");
#endif

  if(registers.int_no < 32)
  {
    printk("\nException...System has been Halt\n");
    printk(KERN_ERR "%s\n", exception_messages[registers.int_no]);
    for(;;);
  }
}
