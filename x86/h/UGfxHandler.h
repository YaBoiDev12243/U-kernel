#pragma once


typedef unsigned char UColor;  


void UGFX_Init();


void UGFX_SetMode(int width, int height, int bpp);


void UGFX_PutPixel(int x, int y, UColor color);
void UGFX_FillRect(int x, int y, int w, int h, UColor color);


typedef struct {
    int width;
    int height;
    UColor* pixels;
} UImage;


void UGFX_DrawImage(int x, int y, UImage* img);


void UGFX_Clear(UColor color);
