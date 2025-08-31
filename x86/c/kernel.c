#include "UVgaHandler.h"

void kernel_main() {
    set_video_mode();
    draw_gradient();

    while (1) __asm__("hlt");
}
