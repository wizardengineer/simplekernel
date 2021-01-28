#ifndef _KERNEL_VGA_I386
#define _KERENL_VGA_I386  

#include <stdint.h>

#define FRAMEBUFFER 0x000B8000

static unsigned int* const framebuffer_rw = (unsigned int*)FRAMEBUFFER;

/**
 * Color for console output
 *
 * @letter L = light color
 * @letter D = dark  color
 */

typedef enum vga_colors 
{
  VGA_BLACK = 0,
  VGA_BLUE  = 1,
  VGA_GREEN = 2,
  VGA_CYAN,
  VGA_RED,
  VGA_MAGENTA,
  VGA_BROWN, 
  VGA_L_GRAY,
  VGA_D_GRAY,
  VGA_L_BLUE,
  VGA_L_GREEN,
  VGA_L_CYAN,
  VGA_L_RED,
  VGA_L_MAGENTA,
  VGA_L_BROWN,
  VGA_WHITE
} vga_colors;

/** 
 * fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */

static inline uint8_t vga_entry_color(vga_colors fg, vga_colors bg) {
	return fg << 4 | bg;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

#endif
