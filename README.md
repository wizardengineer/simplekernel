<p align=center>
  <a href="https://fontmeme.com/graffiti-creator/">
    <img src="https://fontmeme.com/permalink/210130/6d99b8c4939c275c2357cddf398cbcd8.png" alt="graffiti-creator" border="0">
  </a>
</p>


# A Table of Contents of Things I've learnt:

* Modes
    * [Real Mode](#real_mode)
    * [Protected Mode](#protected_mode)
    * [Long Mode](#long_mode)

* Interrupts
    * [What are interrupts](#interrupts)
    * [The use case of IDT](#idt)
    * [The importance IRQ](#irq)
    * [What are exceptions](#exceptions)
    
* Paging
    * [What is paging](#paging)

## Modes
*   <a name="real_mode"> **Real Mode** </a> <br> The name derived from the idea that it's addresses always correspond to real locations in memory, Physical Memory. In comparsion to other modes, Real Mode is a simple and finite 16-bit mode that is presented in every x86 processors. It was the only available mode proved by early x86 designs CPUs. Until the Intel80{286} Protected mode initially came forth. It's finite in comparsion to it's derivatives or successors Protected and Long Mode due to it having less than 1 MB of RAM available for use. There is no hardware-based memory protection (GDT), no virtual memory, no security mitigrations. Forthermore, don't let the finite size impose a misleading conception upon accessibility of Real Mode, It still has access to 32-bit registers (eax, ebx, ...). Before other modes can be loaded, it initiate some programs first within the Real Mode before getting loaded. Real Mode is considerable the true way of having access to the BIOS and it's low level API functionality.
<br>

*   <a name="protected_mode"> **Protected Mode** </a> <br> 

## Resource that undeceive my research:
```
https://wiki.osdev.org/Printing_To_Screen
https://stackoverflow.com/questions/11277652/what-is-the-meaning-of-align-an-the-start-of-a-section
https://code.woboq.org/
http://www.osdever.net/bkerndev/Docs/intro.htm
```
