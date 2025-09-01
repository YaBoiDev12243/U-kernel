#include "UCpuManager.h"
#include "URamHandler.h"
#include "UStoreHandler.h"
#include "UGfxHandler.h"
#include "UVgaHandler.h"


#define MODE_VGA 0
#define MODE_GFX 1

static int bootMode = MODE_GFX;

void kernel_main() {

    UCPU_Init();     
    URAM_Init();     
    USTORE_Init();  


    if (bootMode == MODE_VGA) {
        
        UVGA_SetTextMode();  
        UVGA_PrintString("U-Kernel in text mode!\n");

        
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "Total RAM: %u KB\n", URAM_GetTotal());
        UVGA_PrintString(buffer);
    }
    else if (bootMode == MODE_GFX) {
  
        UGFX_Init();
        UGFX_Clear(0);  

        
        UGFX_FillRect(50, 50, 100, 100, 4);  
        UGFX_FillRect(70, 70, 60, 60, 1);    
    }

    while (1) {
        UCPU_Halt();
    }
}

