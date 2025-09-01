#pragma once

void URAM_Init();

unsigned int URAM_GetTotal();


unsigned int URAM_GetFree();


void* URAM_Alloc(unsigned int size);


void URAM_Free(void* ptr);

