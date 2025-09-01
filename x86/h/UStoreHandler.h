#pragma once


void USTORE_Init();

unsigned int USTORE_GetDriveCount();


int USTORE_Read(unsigned int drive, unsigned int lba, unsigned int count, void* buffer);


int USTORE_Write(unsigned int drive, unsigned int lba, unsigned int count, const void* buffer);


unsigned int USTORE_GetSize(unsigned int drive);
