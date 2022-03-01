#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

char* convretAttrToJSON(const Attribute* a) {
    char* outputString = malloc(sizeof(a + 100000));

    sprintf(outputString, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);

    return outputString;
}

char* convretCircleToJSON(const Circle* a) {
    char* outputString = malloc(sizeof(a + 100000));
    sprintf(outputString, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", a->cx, a->cy, a->r, getLength(a->otherAttributes), a->units);

    return outputString;
}

char* covertRectangleToJSON(const Rectangle* r) {
    char* outputString = malloc(sizeof(r + 100000));
    sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->width, r->height, getLength(r->otherAttributes), r->units);
    return outputString;
}

char* covertPathToJSON(const Path* p) {
    char* outputString = malloc(sizeof(p + 100000));
    sprintf(outputString, "{\"d\":\"%s\",\"numAttr\":%d}", p->data, getLength(p->otherAttributes));

    return outputString;
}
char* covertGroupToJSON(const Group* g) {
    char* outputString = malloc(sizeof(g + 100000));
    sprintf(outputString, "{\"children\":%d,\"numAttr\":%d}", numberOfImmidateChildren(g), getLength(g->otherAttributes));
    return outputString;
}
char* covertSVGtoJSON(const SVG* image) {
    char* outputString = malloc(sizeof(image + 100000));

    sprintf(outputString, "{numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", getLength(image->rectangles), getLength(image->circles), getLength(image->paths), getLength(image->groups));
    return outputString;
}

char* covertAttrListToJSON(const List* list) {
    char* finalOutputString = malloc(sizeof(list + 100000));
    strcpy(finalOutputString, "");
    strcat(finalOutputString, "[");

    char* tempString = malloc(sizeof(char) * 100000);
    void* svcAccElement;
    ListIterator accIter = createIterator((List*)list);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        const Attribute* tmpAttribute = (Attribute*)svcAccElement;
        sprintf(tempString, "%s", convretAttrToJSON(tmpAttribute));
        strcat(finalOutputString, tempString);
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}

char* convertCircListToJSON(const List* list) {
    char* outputString = malloc(sizeof(list + 100000));
    // sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->w, r->h, getLength(r->otherAttributes), r->units);
    
    return outputString;
}

char* convertrectListToJSON(const List* list){
    char* outputString = malloc(sizeof(list + 100000));
    // sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->w, r->h, getLength(r->otherAttributes), r->units);
    return outputString;
}

char* convertpathListToJSON(const List* list){
    char* outputString = malloc(sizeof(list + 100000));
    // sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->w, r->h, getLength(r->otherAttributes), r->units);
    return outputString;
}

char* covertGroupListToJSON(const List* list) {
    char* outputString = malloc(sizeof(list + 100000));

    // sprintf(outputString, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->w, r->h, getLength(r->otherAttributes), r->units);
    return outputString;
}

int numberOfImmidateChildren(const Group* g) {
    int count = 0;
    count += getLength(g->rectangles);
    count += getLength(g->circles);
    count += getLength(g->paths);
    count += getLength(g->groups);
    return count;
}