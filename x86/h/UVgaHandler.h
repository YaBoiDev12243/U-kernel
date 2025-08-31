#ifndef VGA_H
#define VGA_H

#define VIDEO_MEMORY ((unsigned char*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

void set_video_mode();
void putpixel(int x, int y, unsigned char color);
void draw_gradient();

#endif
