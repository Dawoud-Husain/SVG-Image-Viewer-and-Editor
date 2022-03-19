#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

char* convretAttrToJSON(const Attribute* a) {
    char* outputString = calloc(10, sizeof(a + 100000));

    sprintf(outputString, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);

    return outputString;
}

char* convretCircleToJSON(const Circle* a) {
    char* outputString = calloc(10, sizeof(a + 100000));
    sprintf(outputString, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", a->cx, a->cy, a->r, getLength(a->otherAttributes), a->units);

    return outputString;
}

char* covertRectangleToJSON(const Rectangle* r) {
    char* outputString = calloc(10, sizeof(r + 100000));
    sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->width, r->height, getLength(r->otherAttributes), r->units);
    return outputString;
}

char* covertPathToJSON(const Path* p) {
    char* outputString = calloc(10, sizeof(char) + sizeof(p) + 1000000);
    sprintf(outputString, "{\"d\":\"%s\",\"numAttr\":%d}", p->data, getLength(p->otherAttributes));

    return outputString;
}

char* covertGroupToJSON(const Group* g) {
    char* outputString = calloc(10, sizeof(g + 100000));
    sprintf(outputString, "{\"children\":%d,\"numAttr\":%d}", numberOfImmidateChildren(g), getLength(g->otherAttributes));
    return outputString;
}

char* covertSVGtoJSON(const SVG* image) {
    char* outputString = calloc(10, sizeof(image) + 100000);

    sprintf(outputString, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", getLength(image->rectangles), getLength(image->circles), getLength(image->paths), getLength(image->groups));
    return outputString;
}

char* covertAttrListToJSON(const List* list) {
    char* finalOutputString = calloc(10, sizeof(list) + 100000);
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString;
    char* convertOutput;
    void* svcAccElement;

    int count = 0;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        tempString = calloc(10, sizeof(list) + 100000);
        const Attribute* tmpAttribute = (Attribute*)svcAccElement;
        convertOutput = convretAttrToJSON(tmpAttribute);
        sprintf(tempString, "%s", convertOutput);

        strcat(finalOutputString, tempString);

        printf("Tempstring: %s\n", tempString);

        if ((count < (getLength((List*)list)) - 1) && strcmp(tempString, "\0") != 0) {
            strcat(finalOutputString, ",");
        }

        free(tempString);
        free(convertOutput);
        count ++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

char* convertCircListToJSON(const List* list) {
    char* finalOutputString = calloc(10, sizeof(list) + 100000);
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString;
    char* convertOutput;
    void* svcAccElement;

    int count = 0;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        tempString = calloc(10, sizeof(list) + 100000);
        const Circle* tmpCircle = (Circle*)svcAccElement;
        convertOutput = convretCircleToJSON(tmpCircle);
        sprintf(tempString, "%s", convertOutput);

        strcat(finalOutputString, tempString);
        free(tempString);
        free(convertOutput);

        if (count < (getLength((List*)list)) - 1) {
            strcat(finalOutputString, ",");
        }

        count++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

char* convertrectListToJSON(const List* list) {
    char* finalOutputString = calloc(10, sizeof(list) + 100000);
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString;
    char* convertOutput;
    void* svcAccElement;

    int count = 0;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        tempString = calloc(10, sizeof(list) + 100000);
        const Rectangle* tmpRectangle = (Rectangle*)svcAccElement;
        convertOutput = covertRectangleToJSON(tmpRectangle);
        sprintf(tempString, "%s", convertOutput);

        strcat(finalOutputString, tempString);
        free(tempString);
        free(convertOutput);

        if (count < (getLength((List*)list)) - 1) {
            strcat(finalOutputString, ",");
        }

        count++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

char* convertpathListToJSON(const List* list) {
    char* finalOutputString = calloc(10, sizeof(list) + 100000);
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString;
    char* convertOutput;
    void* svcAccElement;

    int count = 0;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        tempString = calloc(10, sizeof(list) + 100000);
        const Path* tmpPath = (Path*)svcAccElement;
        convertOutput = covertPathToJSON(tmpPath);
        sprintf(tempString, "%s", convertOutput);

        strcat(finalOutputString, tempString);
        free(tempString);
        free(convertOutput);

        if (count < (getLength((List*)list)) - 1) {
            strcat(finalOutputString, ",");
        }

        count++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

char* covertGroupListToJSON(const List* list) {
    char* finalOutputString = calloc(10, sizeof(list) + 100000);
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString;
    char* convertOutput;
    void* svcAccElement;

    int count = 0;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        tempString = calloc(10, sizeof(list) + 100000);
        const Group* tmpGroup = (Group*)svcAccElement;
        convertOutput = covertGroupToJSON(tmpGroup);
        sprintf(tempString, "%s", convertOutput);

        strcat(finalOutputString, tempString);
        free(tempString);
        free(convertOutput);

        if (count < (getLength((List*)list)) - 1) {
            strcat(finalOutputString, ",");
        }

        count++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

int numberOfImmidateChildren(const Group* g) {
    int count = 0;
    count += getLength(g->rectangles);
    count += getLength(g->circles);
    count += getLength(g->paths);
    count += getLength(g->groups);
    return count;
}