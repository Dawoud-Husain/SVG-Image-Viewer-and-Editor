// Name: Dawoud Husain
// ID: 1146816
    
#include "SVGParser.h"
#include "SVGAdditionalHelper.h"

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void allocateFlexArray(char* source, char dest[]){
    int index = 0;
    char * tempPointer;
    for (tempPointer = source; *tempPointer != '\0'; tempPointer++) {
        dest[index] = *tempPointer;
        index ++;   
    }
}