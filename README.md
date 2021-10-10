<p align=center>
  <a href="https://fontmeme.com/graffiti-creator/">
    <img src="https://fontmeme.com/permalink/210130/6d99b8c4939c275c2357cddf398cbcd8.png" alt="graffiti-creator" border="0">
  </a>
</p>

# Motivation
This was a great learning curve that seemingly helped me foster more theoretical and conceptual ideas surrounding theories/laws on the underlying mysteries of operating systems and kernels. I had presumed, I had an *okay* idea on how OSs worked. However, creating my own OS was absolutely way more definite compared to just reading about. In my own, honest opinion. This was a way for me to have a better understanding of software I would want to mess with on kernel mode and user mode.

# Resource I relied on:
   * [Intel Manual](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
   * [AMD manual](https://www.amd.com/system/files/TechDocs/24593.pdf)
   * [Reading the Linux Kernel](https://github.com/torvalds/linux/)
   * [Wiki.osdev](https://wiki.osdev.org/)
   * [Shichao Notes](https://notes.shichao.io/utlk/ch2/)
   * [irql0 carbonOS](https://github.com/irql0/carbon)
   * [OSDever](http://www.osdever.net/bkerndev/Docs/intro.htm)

# A Table of Contents of Things I've learnt:
Before we begin, even though the kernel and operating system is 32bit. I will be explaining concepts in 64 bit too, evidently one of them being Long Mode. 

* Modes
    * [Real Mode](#real_mode)
    * [Protected Mode](#protected_mode)
    * [Long Mode](#long_mode)

* Interrupts
    * [APIC and PIC](#apic_pic)
    * [What are interrupts](#interrupts)
    * [Interrupt Request (IRQ)](#irq)
    * [Interrupt Stack Table (IST)](#ist)
    * [Interrupt Service Routine (ISR)](#isr)
    * [What are exceptions](#exceptions)

* Descriptors
    * [Keywords](#keywords)
    * [What exactly is a Table and a Descriptor](#table)
    * [Use case of GDT](#gdt)    
    * [Interrupt Descriptor Table (IDT)](#idt)

* Paging
    * [MMU](#mmu)
    * [What is paging](#paging)

## Modes
*   <a name="real_mode"> **Real Mode** </a> <br> The name derived from the idea that it's addresses always correspond to real locations in memory, Physical Memory. In comparsion to other modes, Real Mode is a simple and finite 16-bit mode that is presented in every x86 processors. It was the only available mode proved by early x86 designs CPUs. Until the Intel80{286} Protected mode initially came forth. It's finite in comparsion to it's derivatives or successors Protected and Long Mode due to it having less than 1 MB of RAM available for use. There is no hardware-based memory protection (GDT), no virtual memory, no security mitigrations. Forthermore, don't let the finite size impose a misleading conception upon accessibility of Real Mode, It still has access to 32-bit registers (eax, ebx, ...). Before other modes can be loaded, it initiate some programs first within the Real Mode before getting loaded. Real Mode is considerable the true way of having access to the BIOS and it's low level API functionality.
<br>

*   <a name="protected_mode"> **Protected Mode** </a> <br> This mode is a featured for 32 bit operating systems, runs after Real Mode. It provides a set of features, if set will enable, will increase more fluent and systematic control over software. Such features include virtual memory, paging, and safe multi-tasking. Through the process of the execution of Protected Mode, memory segmentation is not optional and is needed to be set up for Protected Mode. Thanks to the use grub amazing help, I don't need to program my own Protected Mode as it's provided. I gave a simple example of how protected mode would be programmed in assembly [protected_mode.asm](smkrnl/arch/i386/protected_mode32.asm).

Read up more on Protected Mode in [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3A: System Programming Guide, Part 1; Chapter 3](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) 
*   
<br>

<!-- Things to add
        *Include definition
        *How it's loaded/activated and show the use 
        case of control registers-->

*   <a name="long_mode"> **Long Mode** </a> <br> This mode allows x86_64 architecture computers have access to 64 bit operating systems registers and instructions. The bootloader lies in Real Mode, then the 64 bit kernel checks and switches the CPU to long mode via 64 bit register [EFER](https://en.wikipedia.org/wiki/Control_register#EFER)
<br>

## Interrupts
*   <a name="apic_pic"> **APIC and PIC** </a> <br> Essentaily, these chips or Interrupt Controllers are within systems that helps make computers Interrupt driven. For every interrupt that get signals, the {A}PICs chips will in a orderly matter send those interrupts to the CPU. PIC has been replace with APIC. I won't be doing much explaining on these chips consider that it's more extensive than the mere explanation I've provided...However do read the computer Bible on APIC: [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3A: System Programming Guide, Part 1; Chapter 10](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf) >=}

<br>

*   <a name="interrupts"> **What are Interrupts** </a> <br> You can think of Interrupts as being a signal or data that is being sent by a device such as Keyboard, Solid State Drive, Hard Driver, or Mouse and Software that tell's the CPU that an event happened and need to immediately stop what it's currently doing, to proceed to what sent it the interrupt. 

    E.g. when you move/click a mouse, the mouse controller will send an interrupt to the Interrupt Controller for the CPU, the CPU attention will immediately go to the mouse interrupt and will proceed to execute a routine (mouse movement or clicking). After the mouse interrupt the CPU will continue doing whatever it was before the interrupt or go manage another interrupt if it has been signal to.

```
    
            +------------------------+            +------------+
            |   TYPES OF INTERRUPTS  |------------| Exceptions |
            +------------------------+            +------------+
                   /         \
                  /           \
                 /             \ 
     +------------+           +------------+
     |  HARDWARE  |           |  SOFTWARE  |
     | INTERRUPTS |           | INTERRUPTS |
     +------------+           +------------+
```
<br>

*   <a name="irq"> **Interrupt Request (IQR)** </a> <br> Interrupt Request (IRQ) or Hardware Interrupts, these type of interrupts are yield externally by the chipset that correspond to the Hardware. Through the course of simplekernel, I've only set up 16 ISR for 16 IRQ (0-15).There are two types of IRQs in common use today.
> *IRQ Lines, or Pin-based IRQs:* These are typically statically routed on the chipset. Wires or lines run from the devices on the chipset to an IRQ controller which serializes the interrupt requests sent by devices, sending them to the CPU one by one to prevent races. In many cases, an IRQ Controller will send multiple IRQs to the CPU at once, based on the priority of the device. An example of a very well known IRQ Controller is the Intel 8259 controller chain, which is present on all IBM-PC compatible chipsets, chaining two controllers together, each providing 8 input pins for a total of 16 usable IRQ signalling pins on the legacy IBM-PC.

> *Message Based Interrupts:* These are signalled by writing a value to a memory location reserved for information about the interrupting device, the interrupt itself, and the vectoring information. The device is assigned a location to which it writes either by firmware or by the kernel software. Then, an IRQ is generated by the device using an arbitration protocol specific to the device's bus. An example of a bus which provides message based interrupt functionality is the PCI Bus.
> By wiki.osdev - https://wiki.osdev.org/Interrupts
<br>

*   <a name="ist"> **Interrupt Stack Table (IST)** </a> <br> 
<br>

*   <a name="isr"> **Interrupt Service Request (ISR)** </a> <br> ISR are routines that save the current state of a processor and the set up the approriate registers and segment registers needed for the kernel mode before the C level interrupt handler is called.
<br>


<!-- Things to add
        *Include definitions 
        *Include why they're important
        *Include how you might have seen this in windows driver-->

*   <a name="exceptions"> **What are exceptions** </a> <br> Exceptions are a type of interrupt. These interrupts are generated interally by the CPU. Exceptions are yield by an unexpected event within the CPU.
<br>

## Descriptor
*   <a name="keywords"> **Keywords** </a>
    * **Entry -** The Entry defines a region in memory where to start, along with the limit of region and the access privileges associated with the entry. Access privilege as in telling processor if the OS is running in System (ring 0) or Application (ring 3). It prevents applications or usermode from having access to certain registers/operands and mnemonics. Such as CR registers and cli/sti respectively.
    * **Limit -** The size of the Segment Descriptor
    * **Segment Selector -** They're registers that hold the index of the [Descriptors](#table)

        * to be more explicit, An *index* is not a *selector*
        * Things a Segment Register holds:
            1. Access the Descriptor Table have privilegde too, this is called RPL (Request Privilege level) 
            for every register but for the `cs` is called CPL (Current Privilege Level). They're both serving 
            different purposes, which you can find out in the Intel or AMD manuals.

            2. The table to use for looking into. One table is the GDT the other one is the LDT.

        * An informal rule to conceptually imagine the use of selector:
            So the informal rule is:

            selector = index + table_to_use + privilege
            table_to_use + index = descriptor = all the information about the segment of memory to be used

            where the plus sign is not a arithmetic operation

        * Bit field of segment selector register:
        ``` 
        15                                                 3    2        0
        +--------------------------------------------------+----+--------+
        |          Index                                   | TI |   RPL  |
        +--------------------------------------------------+----+--------+

        TI = Table Indicator: 0 = GDT, 1 = LDT
        
        The TI specify if the Descriptor were dealing with is a GDT or LDT
        IF(TI == 0) THEN
            ... THE DESCRIPTOR IS A GDT
        ELSEIF(TI == 1) THEN
            ... THE DESCRIPTOR IS A LDT
        ```
<br>

*   <a name="table"> **What exactly is a Table and a Descriptor** </a> <br> To simply put it, Descriptor Tables are data structures. You can think of Table as being an array and the Descriptor as being the elements in the Table (the array). The Selector segment holds the index and iterates through the Table in order to point at a Descriptor. 
<br>

*   <a name="gdt"> **Use case of GDT** </a> <br> Being one of the segment descriptor tables, The Global Descriptor Table (GDT) is a protection measure, data structure that uses a heuristic approach in creating sections or segments (aka Segment Descriptors) that are called entries within areas of memory that'll hold certain characteristics of the privileges that have been assign to that memory region. The characteristics that entries, holds the start of where it'll be in memory, limit which is the size of the entry, and the access privilege of the entry.

GDT is 1:1 with Logical Address, An example of the GDT working with the selector:

```
<---- Selector ---->    +----- Segment Selector Register
+-------+----+-----+    v
| Index | TI | RPL | = DS
+-------+----+-----+            GDT                        LDT
   |      |             +---------------------+   +---------------------+
   |      +------------>| Null Descriptor     |   | Null Descriptor     |
   |                    +---------------------+   +---------------------+
   |                    | Descriptor 1        |   | Descriptor 1        |
   |                    +---------------------+   +---------------------+
   |                    |                     |   |                     |
   |                    ...     ...    ...   ...  ...     ...    ...   ...
   |                    |                     |
   |                    +---------------------+
   +------------------->| Descriptor K        |
                        +---------------------+
                        |                     |
                        ...     ...    ...   ...

RPL (Request Privilege Level) describes the privilege for accessing the descriptor

```

We store the all the GDT base (address) and limit (size of our GDT) in the GDTR. The GDTR points to all our GDT Entries in memory, starting from the base. After that, it's then loaded with the [``lgdt``](https://docs.oracle.com/cd/E19455-01/806-3773/instructionset-82/index.html#:~:text=lgdt%20or%20lidt%2C%20when%20used,directly%20in%2080386%20Protected%20Mode.) mnemonic:
```cpp
typedef union _gdt_descriptor
{
  struct
  {
    uint64_t limit_low    : 16;
    uint64_t base_low     : 16;
    uint64_t base_middle  : 8;
    uint64_t access       : 8;
    uint64_t granularity  : 8;
    uint64_t base_high    : 8;
  };
} __attribute__((packed)) gdt_entry_t;



gdt_entry_t gdt_entrys[256];

/* The GDTR (GDT Register) */
struct gdtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtr;

...

gdtr.base = &gdt_entrys;
gdtr.limit = (sizeof(gdt_descr) * 256) - 1)

```

Read up more on it in the [AMD64 Architecture Programmer’s Manual, Volume 2](https://www.amd.com/system/files/TechDocs/24593.pdf), Section 4.7 (pg. 84 - 90{+})

<br>

*   <a name="idt"> **Interrupt Descriptor Table (IDT)** </a> <br> Interrupt Descriptor Tables are close to being the same as Global Descriptor Tables except that the [Descriptor format](#table) for the IDT has no [limits](#keywords). The IDT holds entries or gates for the ISR of every Interrupt.
<br>


## Paging
*   <a name="mmu"> **MMU (Memory Management Unit)** </a> <br> MMU (Memory Management Unit), is a vital hardware that does translation for address logic. It first transforms logical address into linear address, with the magic of the segmenation unit hardware circuit. Then the MMU transforms that linear address into physical address, with the help of the second hardware circuit, paging unit.

<img align=center style="width: 100%" src="https://notes.shichao.io/utlk/figure_2-1.png" /></center>


*   <a name="paging"> **What is Paging** </a> <br> 
> reference to this and on onwards. https://notes.shichao.io/utlk/ch2/#paging-in-hardware
This was by far the most fun I had, I was extremely excited once I understood it. 

*   x86 OS Legacy-paging virtual address with 4KB pages:
<img align=center style="width: 100%" src="https://i.imgur.com/dan9jKU_d.webp?maxwidth=760&fidelity=grand" /></center>

*   x86 OS CR4.PAE paging virtual address with 4KB page:
<img align=center style="width: 100%" src="https://i.imgur.com/EoLVO8F.jpg" /></center>

*   x86_64 (ia-32e) OS CR4.LME/CR4.PAE paging virtual address with 4KB page:
<img align=center style="width: 100%" src="https://i.imgur.com/yxP6VYi.jpg" /></center>

<br>

*   <a name="Page Modes and Control Bits"> **Page Modes and Control Bits** </a> <br>
Paging behavior is controlled by the following control bits:

> •     The WP and PG flags in control register CR0 (bit 16 and bit 31, respectively).

> •     The PSE, PAE, PGE, PCIDE, SMEP, SMAP, and PKE flags in control register CR4 (bit 4, bit 5, bit 7, bit 17, bit 20, bit 21, and bit 22, respectively).


> •     The LME and NXE flags in the IA32_EFER MSR (bit 8 and bit 11, respectively).
> •     The AC flag in the EFLAGS register (bit 18).
> By Chapter 4 of [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3A: System Programming Guide, Part 1; Chapter 4](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf)



> •     The LME and NXE flags in the IA32_EFER MSR (bit 8 and bit 11, respectively).
> •     The AC flag in the EFLAGS register (bit 18).
> Chapter 4 of [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3A: System Programming Guide, Part 1; Chapter 4](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf)

If CR4.PAE and/or CR4.LME is set to 1, then PSE is completely disregarded.

### Commands, if you want to use. 
No terminal added
```
cd smkrnl; make run
```

<br>

## Credit - Special Thanks to the OGs:
  for the spark of inspiration/support on my continuous effort on this project and for helping me understand certain concepts within kernel/OS development. =)
  * [xeroxz](https://twitter.com/_xeroxz?lang=en) 
  * [Daax](https://twitter.com/daax_rynd)
  * [Irql0](https://github.com/irql0) 
  * [Dinero {born anew}](https://github.com/54)
<br>

   *  **Honorable fam mentions**: <br>
   [LLE](https://discord.gg/MvtdVcUsJs) members <br>
   [Red Vice](https://discord.gg/azxCJbh) members such as [Chc4](https://github.com/chc4) and Internal
   <br>

<!--
## Resource that undeceive my research:
```
https://wiki.osdev.org/Printing_To_Screen
https://stackoverflow.com/questions/11277652/what-is-the-meaning-of-align-an-the-start-of-a-section
https://code.woboq.org/
http://www.osdever.net/bkerndev/Docs/intro.htm
https://k.lse.epita.fr/internals/protected_mode.html
http://www.osdever.net/tutorials/
http://www.osdever.net/tutorials/view/the-world-of-protected-mode
https://en.wikipedia.org/wiki/Control_register#:~:text=in%20x86%20series-,CR0,basic%20operation%20of%20the%20processor.
https://www.amd.com/system/files/TechDocs/24593.pdf

For understanding descriptor tables:
https://en.wikipedia.org/wiki/Global_Descriptor_Table
```
-->

