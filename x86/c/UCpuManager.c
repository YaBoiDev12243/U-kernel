#include "UCpuManager.h"



void UCPU_Init() {

}

void UCPU_Halt() {
    asm volatile("hlt");
}

void UCPU_Reset() {
    // simple stub — real reset requires port writes to keyboard controller
}

const char* UCPU_GetVendor() {
    return "U-Kernel Virtual CPU";
}

const char* UCPU_GetModel() {
    return "U-CPU Model 1";
}

unsigned int UCPU_GetFrequency() {
    return 0; // placeholder until timing code is added
}

unsigned int UCPU_GetCoreCount() {
    return 1; // single-core stub for now
}
