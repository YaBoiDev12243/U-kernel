#include "UStoreHandler.h"

void USTORE_Init() {
  
}

unsigned int USTORE_GetDriveCount() {
    return 0; 
}

int USTORE_Read(unsigned int drive, unsigned int lba, unsigned int count, void* buffer) {

    return -1; 
}

int USTORE_Write(unsigned int drive, unsigned int lba, unsigned int count, const void* buffer) {

    return -1; 
}

unsigned int USTORE_GetSize(unsigned int drive) {
    return 0; 
}
