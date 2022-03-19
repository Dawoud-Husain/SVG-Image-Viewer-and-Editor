#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"
#include "SVGA3Helpers.h"

char* createSVGFromJSON() {
    return NULL;
}

bool isValidSVGFromFile(const char* filename, const char* schemaFile) {

    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    if (validateSVG(mySVG, schemaFile) == false) {
        deleteSVG(mySVG);
        return false;
    }

    deleteSVG(mySVG);

    return true;
}

char* getSVGTitle(const char* filename, const char* schemaFile){
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* output = calloc(100, strlen(mySVG->title) * 100);
    strcpy(output, mySVG->title);

    deleteSVG(mySVG);

    return output;
}


char* getSVGDescription(const char* filename, const char* schemaFile){
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* output = calloc(100, strlen(mySVG->description) * 100);
    strcpy(output, mySVG->description);

    deleteSVG(mySVG);

    return output;
}

int getFileSize(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    int fileSize = ftell(fp);
    fclose(fp);

    float floatFileSize = fileSize / 1000;

    if (floatFileSize < 0.5) {
        floatFileSize = 1;
    }

    floatFileSize = round(floatFileSize);
    fileSize = (int) floatFileSize;
   return fileSize;
}

char* getNumsFromFile(const char* filename, const char* schemaFile){
    SVG* mySVG = createValidSVG(filename, schemaFile);

    char * output = SVGtoJSON(mySVG);

    deleteSVG(mySVG);

    return output;
}

char* getRectsImmediateChildrenSummary(const char* filename, const char* schemaFile){
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = rectListToJSON(mySVG->rectangles);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);


    deleteSVG(mySVG);



    return output;
}

char* getCirclesImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = circListToJSON(mySVG->circles);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);

    deleteSVG(mySVG);

    return output;
}

char* getPathsImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = pathListToJSON(mySVG->paths);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);

    deleteSVG(mySVG);

    return output;
}

char* getGroupsImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = groupListToJSON(mySVG->groups);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);

    deleteSVG(mySVG);

    return output;
}


bool updateSVGNameDesc(const char* filename, const char* schemaFile,  const char* newTitle ,const char* newDesc){

    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    strcpy(mySVG->title, newTitle);
    strcpy(mySVG->description, newDesc);

    if(validateSVG(mySVG, schemaFile) == false) {
        return false;
    }

    writeSVG(mySVG, filename);

    deleteSVG(mySVG);
    return true;
}




char* covertAttrListToJSONA3(const List* list) {
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

        //printf("Tempstring: %s\n", tempString);

        if ((count < (getLength((List*)list)) - 1) && strcmp(tempString, "\0") != 0) {
            strcat(finalOutputString, ",");
        }

        free(tempString);
        free(convertOutput);
        count++;
    }

    strcat(finalOutputString, "]");

    return finalOutputString;
}


char* convertrectListToJSONA3(const List* list) {
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
        convertOutput = covertAttrListToJSONA3(tmpRectangle->otherAttributes);
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

char* convertcircListToJSONA3(const List* list) {
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
        convertOutput = covertAttrListToJSONA3(tmpCircle->otherAttributes);
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


char* convertpathListToJSONA3(const List* list) {
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
        convertOutput = covertAttrListToJSONA3(tmpPath->otherAttributes);
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

char* convertGroupListToJSONA3(const List* list) {
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
        convertOutput = covertAttrListToJSONA3(tmpGroup->otherAttributes);
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

char* getRectsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile){

     SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = convertrectListToJSONA3(mySVG->rectangles);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);


    deleteSVG(mySVG);

    return output;
}

char* getCircsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = convertcircListToJSONA3(mySVG->circles);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);


    //printf("CCircleattr: %s\n", output );
    deleteSVG(mySVG);

    return output;
}

char* getPathsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = convertpathListToJSONA3(mySVG->paths);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);

    deleteSVG(mySVG);

    return output;
}

char* getGroupsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    char* string = convertGroupListToJSONA3(mySVG->groups);

    char* output = calloc(100, strlen(string) * 100);
    strcpy(output, string);

    deleteSVG(mySVG);

    return output;
}

bool scaleRect(const char* filename, const char* schemaFile, int scaleFactor){

    SVG* mySVG = createValidSVG(filename, schemaFile);

        if (mySVG == NULL) {
        return false;
    }

    void* svcAccElement;
    List * rects  = getRects(mySVG);


    ListIterator accIter = createIterator((List*)rects);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        
        Rectangle* tmpRectangle = (Rectangle*)svcAccElement;
        tmpRectangle->x = (tmpRectangle->x) * scaleFactor;
        tmpRectangle->y = (tmpRectangle->y) * scaleFactor;
            
    }

    if (validateSVG(mySVG, schemaFile) == false) {
        return false;
    }

    writeSVG(mySVG, filename);

    deleteSVG(mySVG);
    return true;
}

bool scaleCirc(const char* filename, const char* schemaFile, int scaleFactor) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    void* svcAccElement;
    List* circs = getCircles(mySVG);

    ListIterator accIter = createIterator((List*)circs);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Circle* tmpCircle = (Circle*)svcAccElement;
        tmpCircle->cx = (tmpCircle->cx) * scaleFactor;
        tmpCircle->cy = (tmpCircle->cy) * scaleFactor;
        tmpCircle->r = (tmpCircle->r) * scaleFactor;
    }

    if (validateSVG(mySVG, schemaFile) == false) {
        return false;
    }

    writeSVG(mySVG, filename);

    deleteSVG(mySVG);
    return true;
}

bool addRect(const char* filename, const char* schemaFile, float theX, float theY, float theWidth, float theHeight) {
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
    }

    Rectangle *tmpRectangle = (Rectangle *)calloc(sizeof(Attribute) + 100000, 1);

    tmpRectangle->x = theX;
    tmpRectangle->y = theY;
    tmpRectangle->width = theWidth;
    tmpRectangle->height = theHeight;


    List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    tmpRectangle->otherAttributes = attributeList;

    strcpy(tmpRectangle->units, "cm");

    addComponent(mySVG, RECT, (void*)tmpRectangle);

    if (validateSVG(mySVG, schemaFile) == false) {
        return false;
    }

    writeSVG(mySVG, filename);

    deleteSVG(mySVG);
    return true;
}

bool addCirc(const char* filename, const char* schemaFile, float theCX, float theCY, float theR){
    SVG* mySVG = createValidSVG(filename, schemaFile);

    if (mySVG == NULL) {
        return false;
        }

    Circle* tmpCircle = malloc(sizeof(Circle) * 10000);

    tmpCircle->cx = theCX;
    tmpCircle->cy = theCY;
    tmpCircle->r = theR;

    strcpy(tmpCircle->units, "cm");

    List* attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    tmpCircle->otherAttributes = attributeList;

    addComponent(mySVG, CIRC, (void*)tmpCircle);


    if (validateSVG(mySVG, schemaFile) == false) {
        return false;
    }

    writeSVG(mySVG, filename);

    deleteSVG(mySVG);
    return true;
}
