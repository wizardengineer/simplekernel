/* I used irql0 
 * KBDUS: https://github.com/irql0/carbon/blob/07b5bd3de9530152ad084efc0993a80107a29b02/ntgdi/keyboard.c */


#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/keyboard.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static uint8_t _internal_flag = 0x0;

unsigned char       keybdus[KEY_NUM] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
    '9', '0', '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	/* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
    '\'', '`', 0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


unsigned char keybdus_shift[KEY_NUM] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
    '(', ')', '_', '+', '\b',	/* Backspace */
    '\t',			/* Tab */
    'Q', 'W', 'E', 'R',	/* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
    '\"', '~', 0,		/* Left shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
    'M', '<', '>', '?', 0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0, 0, 0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char keybdus_to_ascii(uint8_t scancode)
{
  if(_internal_flag & left_shift_key || _internal_flag & right_shift_key)
  { return keybdus_shift[scancode]; }

  else { return keybdus[scancode]; }
}

void keyboard_handler(regs ctx)
{
  uint8_t scancode = inb(0x60);
  if(scancode & 0x80) { } /* Checks to see if it was released */
  
  else 
  {
    if(scancode & left_shift_key || scancode & right_shift_key)
    {
      _internal_flag = left_shift_key;
    }

    else if(scancode & rl_left_shift_key || scancode & rl_right_shift_key)
    {
      _internal_flag = 0x0;
    }
  }
  putchar(keybdus_to_ascii(scancode));
}

void keyboard_install()
{
  irq_install_handler(1, keyboard_handler);
}

#pragma GCC diagnostic pop
