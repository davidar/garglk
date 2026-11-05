/* Fabularium's optional Bocfel checkpoint extension (GPL-2.0-or-later). */
#ifndef BOCFEL_AUTOSAVE_H
#define BOCFEL_AUTOSAVE_H

#include <stdbool.h>
#include <stdint.h>

/* Fixed-width fields keep the PoC file identical on Android's 32/64-bit ABIs.
 * keep 32K characters and a 256x64 upper grid; grow/version the format
 * if games need larger screens. Historical custom colours are not replayed.
 */
struct autosave_screen {
  uint32_t length, start, text[32768];
  uint32_t grid[64][256];
  uint32_t x, y, height, delayed_height;
  uint32_t style, font[2], previous_font[2], foreground, background;
  uint32_t random[627];
};

extern const char *autosave_path;
bool autosave_checkpoint(void);
bool autosave_capture(struct autosave_screen *screen);
bool autosave_valid(const struct autosave_screen *screen);
void autosave_apply(const struct autosave_screen *screen);
void autosave_random_capture(uint32_t state[627]);
void autosave_random_apply(const uint32_t state[627]);

#endif
