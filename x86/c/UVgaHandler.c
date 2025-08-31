#include "UVgaHandler.h"

void set_video_mode() {
    // BIOS interrupt to set mode 13h (320x200, 256 colors)
    asm volatile (
        "mov $0x00, %%ah\n"
        "mov $0x13, %%al\n"
        "int $0x10\n"
        :
    :
        : "ah", "al"
        );
}

void putpixel(int x, int y, unsigned char color) {
    VIDEO_MEMORY[y * SCREEN_WIDTH + x] = color;
}

void draw_gradient() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            putpixel(x, y, (x + y) % 256);
        }
    }
}
