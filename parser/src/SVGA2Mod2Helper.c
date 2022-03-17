#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

//***********************Insert***************************************

bool insertComponent(SVG* img, elementType type, void* newElement) {
    if (type == SVG_IMG) {
        if (insertCSVGAttr(img, type, newElement) == true) {
            return true;
        }
    }

    else if (type == RECT) {
        if (insertCSVGRectAttr(img, type, newElement) == true) {
            return true;
        }
    }

    else if (type == CIRC) {
        if (insertCSVGCircleAttr(img, type, newElement) == true) {
            return true;
        }
    }

    else if (type == PATH) {
        if (insertCSVGPathAttr(img, type, newElement) == true) {
            return true;
        }
    }

    else if (type == GROUP) {
        if (insertCSVGGroupAttr(img, type, newElement) == true) {
            return true;
        }
    }

    return false;
}

bool insertCSVGAttr(SVG* img, elementType type, void* newElement){

    if (validateAttr((Attribute*)newElement) == false){
        return false;
    }

    insertBack(img->otherAttributes, newElement);
    return true;
}


bool insertCSVGRectAttr(SVG* img, elementType type, void* newElement){
    if (validateRect((Rectangle*)newElement) == false) {
        return false;
    }

    insertBack(img->rectangles, newElement);
    return true;
}

bool insertCSVGCircleAttr(SVG* img, elementType type, void* newElement){
    if (validateCircle((Circle*)newElement) == false) {
        return false;
    }

    insertBack(img->circles, newElement);
    return true;
}

bool insertCSVGPathAttr(SVG* img, elementType type, void* newElement){
    if (validatePath((Path*)newElement) == false) {
        return false;
    }

    insertBack(img->paths, newElement);
    return true;
}
bool insertCSVGGroupAttr(SVG* img, elementType type, void* newElement){
    if (validateGroup((Group*)newElement) == false) {
        return false;
    }

    insertBack(img->groups, newElement);
    return true;

}

//***********************UPDATE***************************************

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
    ListIterator AttributeIter;
    void* elem;

    AttributeIter = createIterator(img->otherAttributes);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)elem;

        if (strcmp(tmpAttribute->name, newAttribute->name) == 0) {
            allocateFlexArray(newAttribute->value, tmpAttribute->value);
            return true;
        }
    }

    return false;
}

bool updateSVGRectAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    int i = 0;
    ListIterator AttributeIter;
    void* elem;

    bool hasEnteredData = false;

    AttributeIter = createIterator(img->rectangles);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        if (elemIndex > i) {
            return false;
        }

        if (i == elemIndex) {
            Rectangle* tmpRectangle = (Rectangle*)elem;

            ListIterator AttributeIter;
            void* elem;

            AttributeIter = createIterator(tmpRectangle->otherAttributes);

            while ((elem = nextElement(&AttributeIter)) != NULL) {
                Attribute* tmpAttribute = (Attribute*)elem;

                if (strcmp(tmpAttribute->name, newAttribute->name) == 0) {
                    allocateFlexArray(newAttribute->value, tmpAttribute->value);
                    hasEnteredData = true;
                    break;
                }
            }

            if (hasEnteredData == false) {
                insertBack(tmpRectangle->otherAttributes, (void*)newAttribute);
                return true;
            }
        }

        i++;
    }

    return false;
}

bool updateSVGCircleAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    int i = 0;
    ListIterator AttributeIter;
    void* elem;

    bool hasEnteredData = false;

    AttributeIter = createIterator(img->circles);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        if (elemIndex > i) {
            return false;
        }

        if (i == elemIndex) {
            Circle* tmpCircle = (Circle*)elem;

            ListIterator AttributeIter;
            void* elem;

            AttributeIter = createIterator(tmpCircle->otherAttributes);

            while ((elem = nextElement(&AttributeIter)) != NULL) {
                Attribute* tmpAttribute = (Attribute*)elem;

                if (strcmp(tmpAttribute->name, newAttribute->name) == 0) {
                    allocateFlexArray(newAttribute->value, tmpAttribute->value);
                    hasEnteredData = true;
                    break;
                }
            }

            if (hasEnteredData == false) {
                insertBack(tmpCircle->otherAttributes, (void*)newAttribute);
                return true;
            }
        }

        i++;
    }

    return false;
}

bool updateSVGPathAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    int i = 0;
    ListIterator AttributeIter;
    void* elem;

    bool hasEnteredData = false;

    AttributeIter = createIterator(img->paths);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        if (elemIndex > i) {
            return false;
        }

        if (i == elemIndex) {
            Path* tmpPath = (Path*)elem;

            ListIterator AttributeIter;
            void* elem;

            AttributeIter = createIterator(tmpPath->otherAttributes);

            while ((elem = nextElement(&AttributeIter)) != NULL) {
                Attribute* tmpAttribute = (Attribute*)elem;

                if (strcmp(tmpAttribute->name, newAttribute->name) == 0) {
                    allocateFlexArray(newAttribute->value, tmpAttribute->value);
                    hasEnteredData = true;
                    break;
                }
            }

            if (hasEnteredData == false) {
                insertBack(tmpPath->otherAttributes, (void*)newAttribute);
                return true;
            }
        }

        i++;
    }

    return false;
}

bool updateSVGGroupAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    int i = 0;
    ListIterator AttributeIter;
    void* elem;

    bool hasEnteredData = false;

    AttributeIter = createIterator(img->groups);

    while ((elem = nextElement(&AttributeIter)) != NULL) {
        if (elemIndex > i) {
            return false;
        }

        if (i == elemIndex) {
            Group* tmpGroup = (Group*)elem;

            ListIterator AttributeIter;
            void* elem;

            AttributeIter = createIterator(tmpGroup->otherAttributes);

            while ((elem = nextElement(&AttributeIter)) != NULL) {
                Attribute* tmpAttribute = (Attribute*)elem;

                if (strcmp(tmpAttribute->name, newAttribute->name) == 0) {
                    allocateFlexArray(newAttribute->value, tmpAttribute->value);
                    hasEnteredData = true;
                    break;
                }
            }

            if (hasEnteredData == false) {
                insertBack(tmpGroup->otherAttributes, (void*)newAttribute);
                return true;
            }
        }

        i++;
    }

    return false;
}
