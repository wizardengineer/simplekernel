<p align=center>
  <a href="https://fontmeme.com/graffiti-creator/">
    <img src="https://fontmeme.com/permalink/210130/6d99b8c4939c275c2357cddf398cbcd8.png" alt="graffiti-creator" border="0">
  </a>
</p>

# Motivation
This was a great learning curve that seemingly helped me foster more theoretical and conceptual ideas surrounding theories and laws on the underlying mysteries of operating systems and kernels. I had presumed, I had a *okay* idea on how OSs worked. However, creating your own OS was absolutely way more definite compared to just reading about, in my own honest opinion. This was a way for me to have a better of software I want to mess with on kernel mode  and user mode.
<br>
Thanks to [xeroxz](https://twitter.com/_xeroxz?lang=en) and [Daax](https://twitter.com/daax_rynd) 
]for the spark of inspiration on my continuous effort on this project.
and Thanks to [Irql0](https://github.com/irql0) for helping me understand certain concepts within kernel/OS development. =)
<br>
# A Table of Contents of Things I've learnt:
Before we begin, even though the kernel and operating system is 32bit. I will be explaining concepts in 64 bit too, evidently one of them being Long Mode. 

* Modes
    * [Real Mode](#real_mode)
    * [Protected Mode](#protected_mode)
    * [Long Mode](#long_mode)

* Interrupts
    * [What are interrupts](#interrupts)
    * [The importance of IRQ, ISA, and ISR](#irq_isa)
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
*   <a name="interrupts"> **What are Interrupts** </a> <br> 
<br>

*   <a name="irq_isa"> **What are the importance of IRQ, ISA, and ISR** </a> <br> 
<br>

<!-- Things to add
        *Include definition 
        *Include why it's important
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

*   <a name="table"> **What exactly is a Table and a Descriptor** </a> <br> You can think of Table as being an array and the Descriptor as being the elements in the Table (the array). 
<br>

*   <a name="gdt"> **Use case of GDT** </a> <br>
<br>

*   <a name="idt"> **Interrupt Descriptor Table** </a> <br> 
<br>

*   <a name="ldt"> **Local Descriptor Table**  </a> <br> 
<br>


## Paging
*   <a name=""> ** </a> <br> 
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
