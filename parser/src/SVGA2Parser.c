#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

//************************************************************************A2MOD1Functions**********************************************************
SVG* createValidSVG(const char* fileName, const char* schemaFile) {
    // An updated version of createSVG. The only difference is that this function validates the xmlDoc returned by
    // the libxml2 function xmlReadFile against an XSD file that represents the SVG standard before doing any
    // further parsing and building the SVG.

    if (fileName == NULL || schemaFile == NULL) {
        return NULL;
    }

    FILE* fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        return NULL;
    }

    fclose(fptr);

    fptr = fopen(schemaFile, "r");
    if (fptr == NULL) {
        return NULL;
    }

    fclose(fptr);

    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    LIBXML_TEST_VERSION
    /*parse the file and get the DOM */
    //doc = xmlReadFile(fileName, schemaFile, 0);

     doc = xmlReadFile(fileName, NULL, 0);

   
    if (doc == NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }

    root_element = xmlDocGetRootElement(doc);

    SVG* createdSVG = malloc(sizeof(SVG) + 100000);

    // Namespace associated with our SVG struct.  May be not be empty.  While a real SVG struct might have
    // multiple namespaces associated with it, we will assume there is only one
    strcpy(createdSVG->namespace, "");
    getNameSpace(root_element, createdSVG->namespace);

    // Title of our SVG struct - from the optional <title> element.  May be empty.
    strcpy(createdSVG->title, "");
    getTitle(root_element, createdSVG->title);

    // Decription of our SVG struct - from the optional <desc> element.  May be empty.
    strcpy(createdSVG->description, "");
    getDescription(root_element, createdSVG->description);

    // Additional SVG attributes - i.e. attributes of the svg XML element.
    // All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.
    // Do not put the namespace here, since it already has its own field
    List* acctsList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    getOtherAttributesFromNode(root_element, acctsList);
    createdSVG->otherAttributes = acctsList;

    // All objects in the list will be of type Rectangle.  It must not be NULL.  It may be empty.
    List* rectsList = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    getRectsFromNode(root_element, rectsList);
    createdSVG->rectangles = rectsList;

    // All objects in the list will be of type Circle.  It must not be NULL.  It may be empty.
    List* circlesList = initializeList(&circleToString, &deleteCircle, &compareCircles);
    getCirclesFromNode(root_element, circlesList);
    createdSVG->circles = circlesList;

    // All objects in the list will be of type Path.  It must not be NULL.  It may be empty.
    // createdSVG->paths = getGroupsFromNode(root_element);
    List* pathsList = initializeList(&pathToString, &deletePath, &comparePaths);
    getPathsFromNode(root_element, pathsList);
    createdSVG->paths = pathsList;

    // All objects in the list will be of type Group.  It must not be NULL.  It may be empty.
    List* groupList = initializeList(&groupToString, &deleteGroup, &compareGroups);
    getGroupsFromNode(root_element, groupList);
    createdSVG->groups = groupList;

    xmlFreeDoc(doc);
    xmlCleanupParser();

    // if (validateSVG(createdSVG, schemaFile) == false) {
    //     return NULL;
    // }

    
    if (validateSVGWithSchema(fileName, schemaFile) == false) {
        deleteSVG(createdSVG);
        return NULL;
    }

    return createdSVG;
}

bool writeSVG(const SVG* img, const char* fileName) {
    //     This function takes an SVG struct and saves it to a file in SVG format.

    if (img == NULL || fileName == NULL) {
        return false;
    }

    covertSVGTOXMLTree(img, fileName);

    return true;
}

bool validateSVG(const SVG* img, const char* schemaFile) {
    // This function takes an SVG struct and the name of a valid SVG schema file, and validates the contents of the
    // SVG struct against an XSD file that represents the SVG standard. It also validated the contents against the 1
    // constraints specified in SVGParser.h.

    writeSVG(img, "test.svg");

    if (img == NULL || schemaFile == NULL) {
        return false;
    }

    if (validateXMLTREE("test.svg", schemaFile) == false) {
        return false;
    }

    if (validateSVGStruct(img) == false) {
        return false;
    }

    if (validateSVGWithSchema("test.svg", schemaFile) == false) {
        return false;
    }

    return true;
}

//************************************************************************A2MOD2Functions**********************************************************

bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    //     This is a generic function that sets the attribute of an SVG, Circle, Rectangle, Path, or Group.

    if (img == NULL || newAttribute == NULL || elemIndex < 0) {
        return false;
    }

    if (validateAttr(newAttribute) == false) {
        return false;
    }

    if (updateElement(img, elemType, elemIndex, newAttribute) == false) {
        return false;
    }

    return true;
}

void addComponent(SVG* img, elementType type, void* newElement) {
    //     This is a generic function for adding a new component to an existing SVG struct.

    if (img == NULL || newElement == NULL) {
        return;
    }

    if (insertComponent(img, type, newElement) == false) {
        return;
    }
}

//************************************************************************A2MOD3Functions**********************************************************

char* attrToJSON(const Attribute* a) {
    //     Converts an Attribute struct to a string in JSON format. {"name":"attrName","value":"attrVal"}

    if (a == NULL) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = convretAttrToJSON(a);

    return output;
}

char* circleToJSON(const Circle* c) {
    // Converts a Circle struct to a string in JSON format: {"cx" : 32, "cy" : 32, "r" : 30, "numAttr" : 0, "units" : "cm"}

    if (c == NULL) {
          char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = convretCircleToJSON(c);

    return output;
}

char* rectToJSON(const Rectangle* r) {
    // Converts a Rectangle struct to a string in JSON format  { "x" : xVal, "y" : yVal, "w" : wVal, "h" : hVal, "numAttr" : attVal, "units" : "unitStr" }

    if (r == NULL) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = covertRectangleToJSON(r);

    return output;
}

char* pathToJSON(const Path* p) {
    // Converts a Path struct to a string in JSON format.The function must return a newly allocated string in the
    //     following format : { "d" : "dVal", "numAttr" : attVal }

    if (p == NULL) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = covertPathToJSON(p);

    return output;
}

char* groupToJSON(const Group* g) {
    // Converts a Group struct to a string in JSON format.The function must return a newly allocated string in the
    //  following format : { "children" : cVal, "numAttr" : attVal }

    if (g == NULL) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = covertGroupToJSON(g);

    return output;
}

char* SVGtoJSON(const SVG* image) {
    // Converts a SVG struct to a string in JSON format.The function must return a newly allocated string in the
    //     following format : { "numRect" : numR, "numCirc" : numC, "numPaths" : numP, "numGroups" : numG }

    if (image == NULL) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "{}");
        return finalOutputString;
    }

    char* output = covertSVGtoJSON(image);
    return output;
}

char* attrListToJSON(const List* list) {
    //     This function will convert a list of Attributes - e.g. the otherAttributes list of a SVG, or otherAttributes list of
    // a Circle - into a JSON string. You can - and should - use attrToJSON function defined above.

    if (list == NULL || getLength((List*)list) == 0) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "[]");
        return finalOutputString;
    }

    char* output = covertAttrListToJSON(list);

    return output;
}

char* circListToJSON(const List* list) {
    // This function will convert a list of Circles into a JSON string.You can - and should - use circToJSON function defined above.

    if (list == NULL || getLength((List*)list) == 0) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "[]");
        return finalOutputString;
    }

    char* output = convertCircListToJSON(list);
    return output;
}

char* rectListToJSON(const List* list) {
    // This function will convert a list of Rectangles into a JSON string.You can - and should - use rectToJSON function defined above

    if (list == NULL || getLength((List*)list) == 0) {
        char* finalOutputString = calloc(10, 100000);   
        strcpy(finalOutputString, "[]");
        return finalOutputString;
    }

    char* output = convertrectListToJSON(list);
    return output;
}

char* pathListToJSON(const List* list) {
    // This function will convert a list of Paths into a JSON string.You can - and should - use pathToJSON function defined above.

    if (list == NULL || getLength((List*)list) == 0) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "[]");
        return finalOutputString;
    }

    char* output = convertpathListToJSON(list);
    return output;
}

char* groupListToJSON(const List* list) {
    //     This function will convert a list of Groups into a JSON string. You can - and should - use groupToJSON function
    // defined above.
    // The function groupListToJSON must return a newly allocated string in the following format:
    // [GroupString1,GroupString2,...,GroupStringN]

    if (list == NULL || getLength((List*)list) == 0) {
        char* finalOutputString = calloc(10, 100000);
        strcpy(finalOutputString, "[]");
        return finalOutputString;
    }

    char* output = covertGroupListToJSON(list);
    return output;
}

SVG* JSONtoSVG(const char* svgString){
    return NULL;
}

Rectangle* JSONtoRect(const char* svgString){
    return NULL;
}

Circle* JSONtoCircle(const char* svgString){
    return NULL;
}