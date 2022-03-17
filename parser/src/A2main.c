// ID: 1146816

#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        return (1);
    }
    printf("HERe\n");

    //********************MOD1 TEST(****************************************)

    //******************************Create VAlid SVG  *********************************
    SVG* mySVG = createValidSVG(argv[1], "svg.xsd");

    if (mySVG == NULL) {
       
        return -1;
    }

    //******************************Write SVG  *********************************

    writeSVG(mySVG, "test.svg");

    //******************************Validate SVG  *********************************
    printf("Validating SVG:\n");

    if (validateSVG(mySVG, "svg.xsd") == false) {
        printf("Image is False\n");
    }

    else {
        printf("Image is valid\n");
    }

    //********************MOD2 TEST(****************************************)

    //******************************Set Test *********************************

    // printf("SVG Before:\n");
    // char *string = SVGToString(mySVG);
    // printf("%s", string);
    // free(string);

    // Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
    // tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
    // strcpy(tmpAttribute->name, "width");
    // allocateFlexArray("6cm", tmpAttribute->value);

    // setAttribute(mySVG, SVG_IMG, 0, tmpAttribute);

    // deleteAttribute(tmpAttribute);

    // printf("SVGAfter\n");

    // string = SVGToString(mySVG);
    // printf("%s", string);
    // free(string);

    // printf("SVG Before:\n");
    // char *string = SVGToString(mySVG);
    // printf("%s", string);
    // free(string);

    // Attribute* tmpAttribute2 = (Attribute*)calloc(sizeof(Attribute) + 100000, 1);
    // tmpAttribute2->name = (char*)calloc(sizeof(char) * 10000, 1);
    // strcpy(tmpAttribute2->name, "fill");
    // allocateFlexArray("black", tmpAttribute2->value);

    // setAttribute(mySVG, RECT, 0, tmpAttribute2);

    // printf("SVGAfter\n");

    // string = SVGToString(mySVG);
    // printf("%s", string);

    //******************************Add Test Pass*********************************

    // Rectangle *tmpRectangle = (Rectangle *)calloc(sizeof(Attribute) + 100000, 1);

    // tmpRectangle->x = 1.121;
    // tmpRectangle->y = 1.3;
    // tmpRectangle->width = 100000;
    // tmpRectangle->height = 100000;
    // strcpy(tmpRectangle->units, "cm");

    // List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    // insertBack(attributeList, tmpAttribute2);
    // tmpRectangle->otherAttributes = attributeList;

    // addComponent(mySVG, RECT,(void*) tmpRectangle);
    // writeSVG(mySVG, "test.svg");

    //********************MOD3 TEST(****************************************)

    //******************************attr to json  *********************************
    void* svcAccElement;
    ListIterator accIter = createIterator(mySVG->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;
        char* str = attrToJSON(tmpAttribute);
        printf("%s\n", str);
        free(str);
    }

    //******************************circ to json  *********************************
    void* circleElement;
    ListIterator circleIter = createIterator(mySVG->circles);
    while ((circleElement = nextElement(&circleIter)) != NULL) {
        Circle* tmpCircle = (Circle*)circleElement;
        char* str = circleToJSON(tmpCircle);
        printf("%s\n", str);
        free(str);
    }

    //******************************rect to json  *********************************
    void* rectangleElement;
    ListIterator iter = createIterator(mySVG->rectangles);
    while ((rectangleElement = nextElement(&iter)) != NULL) {
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;
        char* str = rectToJSON(tmpRectangle);
        printf("%s\n", str);
        free(str);
    }
    //******************************path to json  *********************************
    void* pathElement;
    ListIterator pathIter = createIterator(mySVG->paths);
    while ((pathElement = nextElement(&pathIter)) != NULL) {
        Path* tmpPath = (Path*)pathElement;
        char* str = pathToJSON(tmpPath);
        printf("%s\n", str);
        free(str);
    }

    //******************************group to json  *********************************
    void* groupElement;
    ListIterator groupIter = createIterator(mySVG->groups);
    while ((groupElement = nextElement(&groupIter)) != NULL) {
        Group* tmpGroup = (Group*)groupElement;
        char* str = groupToJSON(tmpGroup);
        printf("%s\n", str);
        free(str);
    }
    //******************************SVG to json  *********************************
    char* str = SVGtoJSON(mySVG);
    printf("%s\n", str);
    free(str);
    

    // //******************************AttrList to json  *********************************
    str = attrListToJSON(mySVG->otherAttributes);
    printf("%s\n", str);
    free(str);
    
    // //******************************CircList to json  *********************************
    str = circListToJSON(mySVG->circles);
    printf("%s\n", str);
    free(str);
    
    // //******************************rectList to json  *********************************
    str = rectListToJSON(mySVG->rectangles);
    printf("%s\n", str);
    free(str);
   
    // //******************************pathList to json  *********************************
    str = pathListToJSON(mySVG->paths);
    printf("%s\n", str);
    free(str);
    
    // //******************************groupList to json  *********************************
    str = groupListToJSON(mySVG->groups);
    printf("%s\n", str);
    free(str);

    deleteSVG(mySVG);
    return 0;
}
