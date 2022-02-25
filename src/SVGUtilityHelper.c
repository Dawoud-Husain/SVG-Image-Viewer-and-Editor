// Name: Dawoud Husain
// ID: 1146816

#include "SVGA1Helpers.h"


void allocateFlexArray(char* source, char dest[]){
    int index = 0;
    char * tempPointer;
    for (tempPointer = source; *tempPointer != '\0'; tempPointer++) {
        dest[index] = *tempPointer;
        index ++;   
    }
}