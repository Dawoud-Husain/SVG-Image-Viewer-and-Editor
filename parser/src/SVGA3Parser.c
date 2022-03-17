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