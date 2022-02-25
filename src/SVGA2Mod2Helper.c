#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

bool updateElement(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {

    if (elemType == SVG_IMG) {
        if (updateSVGAttr(img, elemType, elemIndex, newAttribute) == true) {
            return true;
        }
    }

    else if (elemType == RECT) {
        if (updateSVGRectAttr(img, elemType, elemIndex, newAttribute) == true) {
            return true;
        }
    }

    else if (elemType == CIRC) {
        if (updateSVGCircleAttr(img, elemType, elemIndex, newAttribute) == true) {
            return true;
        }
    }

    else if (elemType == PATH) {
        if (updateSVGPathAttr(img, elemType, elemIndex, newAttribute) == true) {
            return true;
        }
    }

    else if (elemType == GROUP) {
        if (updateSVGGroupAttr(img, elemType, elemIndex, newAttribute) == true) {
            return true;
        }
    }

    return false;
}

bool updateSVGAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    int i = 0;
    ListIterator AttributeIter;
    void* elem;

    AttributeIter = createIterator(img->otherAttributes);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        if (i == elemIndex) {
            Attribute* tmpAttribute = (Attribute*)elem;

            strcpy(newAttribute->name, tmpAttribute->name);
            allocateFlexArray(newAttribute->value, tmpAttribute->value);

            return true;
        }

        if (elemIndex > i) {
            return false;
        }

        i++;
    }

    return true;
}

bool updateSVGRectAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
    return true;
}

bool updateSVGCircleAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
    return true;
}

bool updateSVGPathAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
    return true;
}

bool updateSVGGroupAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
    return true;
}

