#pragma once



void UCPU_Init();


void UCPU_Halt();


void UCPU_Reset();


const char* UCPU_GetVendor();


const char* UCPU_GetModel();


unsigned int UCPU_GetFrequency();


unsigned int UCPU_GetCoreCount();

