#include "UGfxHandler.h"


static unsigned char* vga = (unsigned char*)0xA0000;


static int screenWidth = 320;
static int screenHeight = 200;

void UGFX_Init() {

    asm volatile(
        "mov $0x13, %%ax\n"
        "int $0x10\n"
        :
        :
        : "ax"
    );
    screenWidth = 320;
    screenHeight = 200;
}

void UGFX_SetMode(int width, int height, int bpp) {

    (void)width; (void)height; (void)bpp;
    UGFX_Init();
}

void UGFX_PutPixel(int x, int y, UColor color) {
    if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight) return;
    vga[y * screenWidth + x] = color;
}

void UGFX_FillRect(int x, int y, int w, int h, UColor color) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            UGFX_PutPixel(x + i, y + j, color);
        }
    }
}

void UGFX_DrawImage(int x, int y, UImage* img) {
    for (int j = 0; j < img->height; j++) {
        for (int i = 0; i < img->width; i++) {
            UColor c = img->pixels[j * img->width + i];
            UGFX_PutPixel(x + i, y + j, c);
        }
    }
}

void UGFX_Clear(UColor color) {
    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
            vga[y * screenWidth + x] = color;
        }
    }
}
