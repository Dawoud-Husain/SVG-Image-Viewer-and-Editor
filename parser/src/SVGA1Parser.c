// Name: Dawoud Husain
// ID: 1146816

//Citation: Parts of the createSVG function was taken from the CIS2750 libXmlExample.c authored by Dodji Seketeli

#include "SVGA1Helpers.h"


SVG* createSVG(const char* fileName){
    // This function does the parsing and allocates an SVG struct. It accepts a filename, which must not be modified
    // in any way. If the file has been parsed successfully, a pointer to the newly created SVG struct is returned. If the
    // parsing fails for any reason, the function must return NULL.
    // Parsing can fail for a number of reasons, but libxml hides them from us. The xmlReadFile function will
    // simply return NULL instead of an XML doc if the file is invalid for any reason.

    // if(validateXML(fileName) == -1){
    //     printf("invalid\n");
    //     return NULL;
    // }

    // Get The Root Element 
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION
    /*parse the file and get the DOM */
    doc = xmlReadFile(fileName, NULL, 0);
    if (doc == NULL) {
        //printf("error: could not parse file\n");
        xmlFreeDoc(doc);
        xmlCleanupParser();
        
        return NULL;
    }

    
    root_element = xmlDocGetRootElement(doc);

    SVG * createdSVG = malloc(sizeof(SVG) + 100000);

    //Namespace associated with our SVG struct.  May be not be empty.  While a real SVG struct might have
    //multiple namespaces associated with it, we will assume there is only one
    strcpy(createdSVG->namespace, "");
    getNameSpace(root_element, createdSVG->namespace);
    
    //Title of our SVG struct - from the optional <title> element.  May be empty.
     strcpy(createdSVG->title, "");
    getTitle(root_element, createdSVG->title);


    //Decription of our SVG struct - from the optional <desc> element.  May be empty.
    strcpy(createdSVG->description, "");
    getDescription(root_element, createdSVG->description);


    //Additional SVG attributes - i.e. attributes of the svg XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.  
    //Do not put the namespace here, since it already has its own field
    List* acctsList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    getOtherAttributesFromNode(root_element, acctsList);
    createdSVG->otherAttributes = acctsList; 


    // //All objects in the list will be of type Rectangle.  It must not be NULL.  It may be empty.
    List* rectsList = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    getRectsFromNode(root_element, rectsList);
    createdSVG->rectangles = rectsList; 

    // //All objects in the list will be of type Circle.  It must not be NULL.  It may be empty.
    List* circlesList = initializeList(&circleToString, &deleteCircle, &compareCircles);
    getCirclesFromNode(root_element, circlesList);
    createdSVG->circles = circlesList; 

    // //All objects in the list will be of type Path.  It must not be NULL.  It may be empty.
    // createdSVG->paths = getGroupsFromNode(root_element);
    List* pathsList = initializeList(&pathToString, &deletePath, &comparePaths);
    getPathsFromNode(root_element, pathsList);
    createdSVG->paths = pathsList; 

    // //All objects in the list will be of type Group.  It must not be NULL.  It may be empty.
    List* groupList = initializeList(&groupToString, &deleteGroup, &compareGroups);
    getGroupsFromNode(root_element, groupList);
    createdSVG->groups = groupList; 
   
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return createdSVG;
}



char* SVGToString(const SVG* img){
// This function returns a humanly readable string representation of the entire vector image object. It will be
// used mostly by you, for debugging your parser. It must not modify the vector image object in any way. The
// function must allocate the string dynamically.

    if(img == NULL){
        return NULL;
    }

    char *OutputString;
    
    OutputString = (char*) malloc(sizeof(char) * 10000024);
    strcpy(OutputString, "");

    strcat(OutputString, "\n\n");
    strcat(OutputString, "Namespace: \n");
    strcat(OutputString, img->namespace);
    strcat(OutputString, "\n\n");

    strcat(OutputString, "*********************************************************** \n");
    //Title of our SVG struct - from the optional <title> element.  May be empty.
   
    strcat(OutputString, "Title: \n");
    strcat(OutputString,img->title);
    strcat(OutputString, "\n\n");
    strcat(OutputString, "*********************************************************** \n");
    
    // //Decription of our SVG struct - from the optional <desc> element.  May be empty.
    strcat(OutputString, "Description: \n");
    strcat(OutputString,img->description);
    strcat(OutputString, "\n\n");
    strcat(OutputString, "***************************OTHER ATTRIBUTES******************************** \n");
   
    void* svcAccElement;
    ListIterator accIter = createIterator(img->otherAttributes);
	while ((svcAccElement = nextElement(&accIter)) != NULL){
        
		Attribute* tmpAttribute = (Attribute*)svcAccElement;
		char* str = attributeToString(tmpAttribute);

        strcat(OutputString, "Other Attributes\n");
        strcat(OutputString,str);
        strcat(OutputString, "\n\n");
		free(str);
	}
    strcat(OutputString, "*************************RECTANGLES********************************** \n");

    // //All objects in the list will be of type Rectangle.  It must not be NULL.  It may be empty.
    void* rectangleElement;
    ListIterator iter = createIterator(img->rectangles);
	while ((rectangleElement = nextElement(&iter)) != NULL){
		Rectangle* tmpRectangle = (Rectangle*)rectangleElement;
		char* str = rectangleToString(tmpRectangle);
        strcat(OutputString, "Rectangle\n");
        strcat(OutputString,str);
        strcat(OutputString, "\n\n");
		free(str);
	}
    strcat(OutputString, "**************************CIRCLES********************************* \n");
	
    // //All objects in the list will be of type Circle.  It must not be NULL.  It may be empty.
    void* circleElement;
    ListIterator circleIter = createIterator(img->circles);
	while ((circleElement = nextElement(&circleIter)) != NULL){
		Circle* tmpCircle = (Circle*)circleElement;
		char* str = circleToString(tmpCircle);
        strcat(OutputString, "Circle\n");
        strcat(OutputString,str);
        strcat(OutputString, "\n\n");
		free(str);
	}

    // //All objects in the list will be of type Path.  It must not be NULL.  It may be empty.
    strcat(OutputString, "**************************PATHS********************************* \n");
    void* pathElement;
    ListIterator pathIter = createIterator(img->paths);
	while ((pathElement = nextElement(&pathIter)) != NULL){
		Path* tmpPath = (Path*)pathElement;
		char* str = pathToString(tmpPath);
        strcat(OutputString, "Path\n");
        strcat(OutputString,str);
        strcat(OutputString, "\n\n");
		free(str);
	}

     // //All objects in the list will be of type Group.  It must not be NULL.  It may be empty.
    strcat(OutputString, "**************************GROUPS********************************* \n");

    void* groupElement;
    ListIterator groupIter = createIterator(img->groups);
	while ((groupElement = nextElement(&groupIter)) != NULL){
		Group* tmpGroup = (Group*)groupElement;
		char* str = groupToString(tmpGroup);
        strcat(OutputString, "Group: \n\n");
        strcat(OutputString,str);
        strcat(OutputString, "\n\n");
		free(str);
	}

    strcat(OutputString, "*****************************END OF SVG TO STRING****************************** \n");

    return OutputString;
}

void deleteSVG(SVG* img){
    // This function deallocates the object, including all of its subcomponents.

    if(img == NULL){
        return;
    }

    freeList(img->otherAttributes);
    freeList(img->rectangles);	
    freeList(img->circles);	
    freeList(img->paths);
    freeList(img->groups);
    free(img);
}


// Function that returns a list of all rectangles in the SVG struct. If there are none, it returns an empty list (not a NULL pointer)
List* getRects(const SVG* img){

    if(img == NULL){
        return NULL;
    }

    List* rectsList = initializeList(&rectangleToString, &dummyDelete, &compareRectangles);

    void* rectangleElement;
    ListIterator iter = createIterator(img->rectangles);
    while ((rectangleElement = nextElement(&iter)) != NULL){
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;
        insertBack(rectsList, (void*)tmpRectangle);
    }

    getRectsFromAllGroups(rectsList, img->groups);

    return rectsList;
}

// Function that returns a list of all circles in the SVG struct. If there are none, it returns an empty list (not a NULL pointer).
List* getCircles(const SVG* img){

    if(img == NULL){
        return NULL;
    }

    List* circlesList = initializeList(&circleToString, &dummyDelete, &compareCircles);

    void* circleElement;
    ListIterator iter = createIterator(img->circles);
    while ((circleElement = nextElement(&iter)) != NULL){
        Circle* tmpCircle = (Circle*)circleElement;
        insertBack(circlesList, (void*)tmpCircle);
    }

    getCirclesFromAllGroups(circlesList, img->groups);

    return circlesList;
}

//Function that returns a list of all paths in the SVG struct. If there are none, it returns an empty list (not a NULL pointer).
List* getPaths(const SVG* img){

    if(img == NULL){
        return NULL;
    }

    List* pathsList = initializeList(&pathToString, &dummyDelete, &comparePaths);

    void* pathElement;
    ListIterator iter = createIterator(img->paths);
    while ((pathElement = nextElement(&iter)) != NULL){
        Path* tmpPath = (Path*)pathElement;
        insertBack(pathsList, (void*)tmpPath);
    }

    getPathsFromAllGroups(pathsList, img->groups);

    return pathsList;
}

// Function that returns a list of all groups in the SVG struct. If there are none, it returns an empty list (not a NULL pointer)


List* getGroups(const SVG* img){

    if(img == NULL){
        return NULL;
    }

    List* groupsList = initializeList(&groupToString, &dummyDelete, &compareGroups);

    void* groupElement;
    ListIterator iter = createIterator(img->groups);
    while ((groupElement = nextElement(&iter)) != NULL){
        Group* tmpGroup = (Group*)groupElement;
        insertBack(groupsList, (void*)tmpGroup);
    }

    getGroupsFromAllGroups(groupsList, img->groups);

    return groupsList;
}

/* For the four "num..." functions below, you need to search the SVG struct for components that match the search 
  criterion.  You may wish to write some sort of a generic searcher fucntion that accepts a struct, a predicate function,
  and a dummy search record as arguments.  We will discuss such search functions in class

 NOTE: For consistency, use the ceil() function to round the floats up to the nearest integer once you have computed 
 the number you need.  See A1 Module 2 for details.

 *@pre SVG struct exists, is not null, and has not been freed.  The search criterion is valid
 *@post SVG struct has not been modified in any way
 *@return an int indicating how many objects matching the criterion are contained in the struct
 *@param obj - a pointer to an SVG struct
 *@param 2nd - the second param depends on the function.  See details below
 */   

// Function that returns the number of all rectangles with the specified area. Return 0 if no such rectangles are found, or if any of the arguments are invalid.
int numRectsWithArea(const SVG* img, float area){

    if(img == NULL){
        return 0;
    }

    List* rectsList = getRects(img);

    if(rectsList == NULL){
        return 0;
    }

    int result = compare(rectsList, compareRectanglesAreaFunc, &area);
    freeList(rectsList);

    return result;
}
   

//Function that returns the number of all circles with the specified area. Return 0 if no such circles are found, or if any of the arguments are invalid.
int numCirclesWithArea(const SVG* img, float area){

    if(img == NULL){
        return 0;
    }

     List* circlesList = getCircles(img);

    if(circlesList == NULL){
        return 0;
    }
    
    int result = compare(circlesList, compareCirclesAreaFunc, &area);
    freeList(circlesList);
    return result;
}

// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(const SVG* img, const char* data){

    if(img == NULL){
        return 0;
    }

    List* pathsList = getPaths(img);

    if(pathsList == NULL){
        return 0;
    }

    int result =  comparePathsMain(pathsList, data);
    freeList(pathsList);
    return result;
}

// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(const SVG* img, int len){

    if(img == NULL){
        return 0;
    }

    int numGroupsWithLen = sumAllGroupsWithLen(img->groups, len);

    return numGroupsWithLen;
}

/*  Function that returns the total number of Attribute structs in the SVG struct - i.e. the number of Attributes
    contained in all otherAttributes lists in the structs making up the SVG struct
    *@pre SVG struct  exists, is not null, and has not been freed.  
    *@post SVG has not been modified in any way
    *@return the total length of all attribute structs in the SVG
    *@param obj - a pointer to an SVG struct
*/
int numAttr(const SVG* img){

    if(img == NULL){
        return 0;
    }
    
    int numAttr = sumAllAttr(img);

    return numAttr;
}


