<p align=center>
  <a href="https://fontmeme.com/graffiti-creator/">
    <img src="https://fontmeme.com/permalink/210130/6d99b8c4939c275c2357cddf398cbcd8.png" alt="graffiti-creator" border="0">
  </a>
</p>

# Motivation
This was a great learning curve that seemingly helped me foster more theoretical and conceptual ideas surrounding theories and laws on the underlying mysteries of operating systems and kernels. I had presumed, I had a *okay* idea on how OSs worked. However, creating your own OS was absolutely way more definite compared to just reading about, in my own honest opinion. This was a way for me to have a better of software I want to mess with on kernel mode  and user mode.

# A Table of Contents of Things I've learnt:
Before we begin, even though the kernel and operating system is 32bit. I will be explaining concepts in 64 bit too, evidently one of them being Long Mode. 

* Modes
    * [Real Mode](#real_mode)
    * [Protected Mode](#protected_mode)
    * [Long Mode](#long_mode)

* Interrupts
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
    * [Local Descriptor Table (LDT)](#ldt)

* Paging
    * [What is paging](#paging)

## Modes
*   <a name="real_mode"> **Real Mode** </a> <br> The name derived from the idea that it's addresses always correspond to real locations in memory, Physical Memory. In comparsion to other modes, Real Mode is a simple and finite 16-bit mode that is presented in every x86 processors. It was the only available mode proved by early x86 designs CPUs. Until the Intel80{286} Protected mode initially came forth. It's finite in comparsion to it's derivatives or successors Protected and Long Mode due to it having less than 1 MB of RAM available for use. There is no hardware-based memory protection (GDT), no virtual memory, no security mitigrations. Forthermore, don't let the finite size impose a misleading conception upon accessibility of Real Mode, It still has access to 32-bit registers (eax, ebx, ...). Before other modes can be loaded, it initiate some programs first within the Real Mode before getting loaded. Real Mode is considerable the true way of having access to the BIOS and it's low level API functionality.
<br>

*   <a name="protected_mode"> **Protected Mode** </a> <br> 
<br>

<!-- Things to add
        *Include definition
        *How it's loaded/activated and show the use 
        case of control registers-->

*   <a name="long_mode"> **Long Mode** </a> <br> 
<br>

## Interrupts
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

*   <a name="irq_ist"> **Importance of IRQ IST and ISR** </a> <br> 
<br>

<!-- Things to add
        *Include definitions 
        *Include why they're important
        *Include how you might have seen this in windows driver-->

*   <a name="exceptions"> **What are exceptions** </a> <br> 
<br>

## Descriptor
*   <a name="keywords"> **Keywords** </a>
    * **Entry -** The Entry defines a region in memory where to start, along with the limit of region and the access privileges associated with the entry. Access privilege as in telling processor if the OS is running in System (ring 0) or Application (ring 3). It prevents applications or usermode from having access to certain registers/operands and mnemonics. Such as CR registers and cli/sti respectively.
    * **Limit -** The size of the Segment
    Descriptor
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
        ```
<br>

*   <a name="table"> **What exactly is a Table and a Descriptor** </a> <br> To simply put it, you can think of Table as being an array and the Descriptor as being the elements in the Table (the array). The Selector segment holds the index and iterates through the Table in order to point at a Descriptor. 
<br>

*   <a name="gdt"> **Use case of GDT** </a> <br> Being one of the segment descriptor tables, The Global Descriptor Table (GDT) is a protection measure, data structure that uses a heuristic approach in creating sections or segments (aka Segment Descriptors) that are called entries within areas of memory that hold certain characteristics on the privileges that have been assign to that memory region. The characteristics that the entries hold are the start of where it's be in memory, limit which is the size of teh entry, and the access privilege of the entry.

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

We store the all the GDT base (address) and limit (size of our GDT) in the GDTR. The GDTR points to all our GDT Entries in memory, starting from the base. After that, it's then loaded with the [``lgdt``]() mnemonic:
```cpp
typedef struct gdt_descriptor
{
    union
    {
        uint64_t limit_low : 16;
        uint64_t base_low  : 16;
        uint64_t base_mid  : 8;
        uint64_t access    : 8;
        uint64_t gran      : 8;
        uint64_t base_high : 8;
    } 
} __attribute__((packed)) gdt_descr;

gdt_descr gdt_entrys[256];

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

Read up more on it in the [AMD64 Architecture Programmer’s Manual, Volume 2](https://www.amd.com/system/files/TechDocs/24593.pdf), Section 4.7 (pg. 84 - 90)

<br>

*   <a name="idt"> **Interrupt Descriptor Table** </a> <br> 
<br>

*   <a name="ldt"> **Local Descriptor Table**  </a> <br> 
<br>


## Paging
*   <a name=""> ** </a> <br> 
<br>

## Thanks for the help:
<br>
Thanks to the fams [xeroxz](https://twitter.com/_xeroxz?lang=en), [Daax](https://twitter.com/daax_rynd) and [Irql0](https://github.com/irql0) for the spark of inspiration on my continuous effort on this project and for helping me understand certain concepts within kernel/OS development. =)

**Honorable fam mentions**:
Some [LLE](https://discord.gg/MvtdVcUsJs) members
[Red Vice](https://discord.gg/azxCJbh) members such as Chc4 and Internal
<br>


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
