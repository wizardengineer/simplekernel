#ifndef __KEYBOARD_DRIVER_
#define __KEYBOARD_DRIVER_

#define KEY_NUM 128

#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <io/serial_port.h>

enum _my_recorded_keys
{
  /* F-Keys :: might add more */
  f1_key = 0x3B,
  f2_key = 0x3C,
  f3_key = 0x3D,
  f4_key = 0x3E,
  /* Shift, Alt, etc ...*/
  left_shift_key  = 0x2A,
  right_shift_key = 0x36,
  rl_left_shift_key  = 0x2A, // release
  rl_right_shift_key = 0x36  // release

};

/* Maybe use this in the future */
typedef enum _keyboard_state
{
  key_pressed,
  key_release,
} keyboard_state;

unsigned char       keybdus[KEY_NUM];
unsigned char keybdus_shift[KEY_NUM];

void keyboard_install();

void keyboard_handler(regs ctx);
unsigned char keybdus_to_ascii(unsigned char scancode);

#endif
