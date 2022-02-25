#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

//************************************************************************A2MOD1Functions**********************************************************
SVG* createValidSVG(const char* fileName, const char* schemaFile) {
    // An updated version of createSVG. The only difference is that this function validates the xmlDoc returned by
    // the libxml2 function xmlReadFile against an XSD file that represents the SVG standard before doing any
    // further parsing and building the SVG.
    // This function does the parsing and allocates an SVG struct. It accepts the name of the SVG file, and the name
    // of the XSD file. If the file contains a valid SVG struct and has been parsed successfully, a pointer to the to the
    // newly created SVG object is returned. If the parsing fails for any reason - invalid XML format, invalid SVG
    // format, etc. - the function must return NULL.

    if (fileName == NULL || schemaFile == NULL) {
        return NULL;
    }

    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    LIBXML_TEST_VERSION
    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, schemaFile, 0);
    if (doc == NULL) {
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

    if (validateSVG(createdSVG, schemaFile) == false){
        return NULL;
    }

    return createdSVG;
}

bool writeSVG(const SVG* img, const char* fileName) {
    //     This function takes an SVG struct and saves it to a file in SVG format. Its arguments are an SVG and the name of
    // a new file. It must return true if the write was successful, and false is the write failed for any reason - invalid
    // output file name, etc.. This function can assume that the doc argument has already been validated with
    // validateSVG, which is discussed below. It must still make sure the arguments are not NULL.
    // For saving floating point numerical data, use full precision: ftoa() or %f. Do not truncate the decimal points
    // for your floats - include all of them.

    if (img == NULL || fileName == NULL) {
        return false;
    }

    covertSVGTOXMLTree(img, fileName);

    return true;
}

bool validateSVG(const SVG* img, const char* schemaFile) {
    // This function takes an SVG struct and the name of a valid SVG schema file, and validates the contents of the
    // SVG struct against an XSD file that represents the SVG standard. It also validated the contents against the 1
    // constraints specified in SVGParser.h. It returns true if the SVG struct contains valid data and false
    // otherwise.
    // There are two aspects to SVG struct validity. First, its contents must represent a valid SVG struct once
    // converted to XML. This can be validated using a method similar to what do in createValidSVG.
    // The second aspect is whether the SVG violates any of the constraints specified in the SVGParser.h. Some of
    // these constraints reflect the SVG specification. For example, the SVG documentation states that a circle radius
    // cannot be negative. However, validating a libxml tree against the SVG schema file will not catch this violation -
    // as long as the radius is a valid number, libxml will consider the underlying XML document to be valid and fully
    // compliant with the schema.
    // In addition, there are constraints that enforce the internal consistency of the data structures in the SVG - for
    // example, all pointers in an SVG must be initialized and must not be NULL.
    // This means that validateSVG must manually check the constraints of the struct against the specifications
    // listed in SVGParser.h - ensure that the numbers are within valid ranges, lists are not NULL, etc.

    // contents must represent a valid SVG struct once converted to XML

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

    return true;
}

//************************************************************************A2MOD2Functions**********************************************************

bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute) {
    //     This is a generic function that sets the attribute of an SVG, Circle, Rectangle, Path, or Group. For example,
    // you might decide to add a fill attribute to a Rectangle, change the radius of a Circle, etc..
    // Note that while this function operates only on elements that are immediate children on the svg element in the
    // original SVG file. In other words, it can set an attribute of a Rectangle in SVG->rectangles, or a Group in
    // SVG->groups, but not attributes of a Rectangle belonging to a Group in SVG->groups.
    // For example, if we create an SVG from quad01.svg, we can change the attributes of any of the three groups, or
    // the attributes of the path at the bottom of the file. However, we cannot use this function to access elements
    // deeper in the XML tree, e.g. the rectangle or path within the first group.

    if (img == NULL || newAttribute == NULL) {
        return false;
    }
    
    if (updateElement(img, elemType, elemIndex, newAttribute) == false) {
        return false;
    }

    return true;
}

void addComponent(SVG* img, elementType type, void* newElement) {
    //     This is a generic function for adding a new component to an existing SVG struct. New components are always
    // added at the end of the component list. This function only needs to handle Circles, Rectangles, and Paths.
    // The arguments are:
    // - img: Pointer to the SVG we are modifying
    // - type: Value indicating which struct we are modifying, i.e. CIRC, RECT, or PATH. We will use it so that we
    // know how to dereference the generic newComponent pointer.
    // - newComponent: the new component.
    // This function will append the new component to the end of the appropriate list in and SVG struct, after
    // checking the elemType variable. It must do nothing if any of the arguments are invalid
}

//************************************************************************A2MOD3Functions**********************************************************

char* attrToJSON(const Attribute* a) {
    //     Converts an Attribute struct to a string in JSON format. The function must return a newly allocated string in the
    // following format:
    // 1
    // {"name":"attrName","value":"attrVal"}
    // where attrName is the name of the attribute, and attrVal is its value. Note the quotes in the string - they are part
    // of the format.
    // For example, given an Attribute with the name fill, and value red the resulting string would be:
    // {"name":"fill","value":"red"}
    // The format must be exactly as specified. Do not add any spaces, newlines, or change capitalization.
    // The returned string contents for this function - and all the other ...ToJSON functions below - will contain double-
    // quote characters, so you will need to use the escape sequence \" in your code.
    // This function must not modify its argument in any way.
    // If the argument a is NULL, the function must return the string {} (there is no space there - just two chars).

    return NULL;
}

char* circleToJSON(const Circle* c) {
    // Converts a Circle struct to a string in JSON format.The function must return a newly allocated string in the
    //         following
    //         format(note the presence / absence of quotes around values) : {"cx" : xVal, "cy" : yVal, "r" : rVal, "numAttr" : attVal, "units" : "unitStr"} where : -xVal is the centre x coordinate -
    //     yVal is the centre y coordinate - rVal is radius - attVal is the number of elements in the otherAttributes list of that circle - unitStr is the units For example : -given a Circle created from<circle cx = "32" cy = "32" r = "30" fill = "#ffdd67" />,
    // the corresponding
    //     string would be { "cx" : 32, "cy" : 32, "r" : 30, "numAttr" : 1, "units" : "" }
    // -given a Circle created from<circle cx = "32cm" cy = "32cm" r = "30cm" />, the corresponding string would be{"cx" : 32, "cy" : 32, "r" : 30, "numAttr" : 0, "units" : "cm"}
    // This function must not modify its argument in any way.If the argument c is NULL, the function must return the string{}(there is no space there - just two chars).

    return NULL;
}

char* rectToJSON(const Rectangle* r) {
    // Converts a Rectangle struct to a string in JSON format.The function must return a newly allocated string in the
    //     following format : { "x" : xVal, "y" : yVal, "w" : wVal, "h" : hVal, "numAttr" : attVal, "units" : "unitStr" }

    //     where:
    // - xVal is the x coordinate
    // - yVal is the y coordinate
    // - wVal is the width
    // - hVal is the height
    // - attVal is the number of elements in the otherAttributes list of that rectangle
    // - unitStr is the units

    return NULL;
}

char* pathToJSON(const Path* p) {
    // Converts a Path struct to a string in JSON format.The function must return a newly allocated string in the
    //     following format : { "d" : "dVal", "numAttr" : attVal }

    return NULL;
}

char* groupToJSON(const Group* g) {
    // Converts a Group struct to a string in JSON format.The function must return a newly allocated string in the
    //  following format : { "children" : cVal, "numAttr" : attVal }

    return NULL;
}

char* SVGtoJSON(const SVG* image) {
    // Converts a SVG struct to a string in JSON format.The function must return a newly allocated string in the
    //     following format : { "numRect" : numR, "numCirc" : numC, "numPaths" : numP, "numGroups" : numG }

    return NULL;
}

char* attrListToJSON(const List* list) {
    //     This function will convert a list of Attributes - e.g. the otherAttributes list of a SVG, or otherAttributes list of
    // a Circle - into a JSON string. You can - and should - use attrToJSON function defined above.

    return NULL;
}

char* circListToJSON(const List* list) {
    // This function will convert a list of Circles into a JSON string.You can - and should - use circToJSON function defined above.

    return NULL;
}

char* rectListToJSON(const List* list) {
    // This function will convert a list of Rectangles into a JSON string.You can - and should - use rectToJSON function defined above

    return NULL;
}

char* pathListToJSON(const List* list) {
    // This function will convert a list of Paths into a JSON string.You can - and should - use pathToJSON function defined above.

    return NULL;
}

char* groupListToJSON(const List* list) {
    //     This function will convert a list of Groups into a JSON string. You can - and should - use groupToJSON function
    // defined above.
    // The function groupListToJSON must return a newly allocated string in the following format:
    // [GroupString1,GroupString2,...,GroupStringN]

    return NULL;
}
