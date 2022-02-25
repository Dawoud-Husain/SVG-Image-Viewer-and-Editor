#ifndef SVGA1ADDITIONALHELPER_H
#define SVGA1ADDITIONALHELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>

#include "SVGA1Helpers.h"
#include "SVGParser.h"

// Utility Functions

//Place a char* into a dynamic array
void allocateFlexArray(char str[], char* src);

// Module 1 Helper Functions

//get the namespace from root node
void  getNameSpace(xmlNode * a_node, char namespace[256]);

//get the title from root node
void getTitle(xmlNode * a_node, char title[256]);

//get the description
void getDescription(xmlNode * a_node, char description[256]);

//The following get functions get the SVG structs from the root node

List* getRectsFromNode(xmlNode * a_node, List* rectsList);
List* getCirclesFromNode(xmlNode * a_node, List * circlesList);
List* getGroupsFromNode(xmlNode * a_node, List* groupsList);
List* getPathsFromNode(xmlNode * a_node, List* pathsList);
List* getOtherAttributesFromNode(xmlNode * a_node, List* attributeList);


//The following get functions are used the getGroupsFromNode function

Rectangle * getRectFromSingleNode(xmlNode * a_node);
Circle * getCircleFromSingleNode(xmlNode * a_node);
Path * getPathFromSingleNode(xmlNode * a_node);
Group * getGroupFromSingleNode(xmlNode * a_node);


// Module 2 Helper Functions

//The folowing get functions get all the shapes in the SVG struct

void getRectsFromAllGroups(List* rectsList, List*groupsList);
void getCirclesFromAllGroups(List* circlesList, List*groupsList);
void getPathsFromAllGroups(List* circlesList, List*groupsList);
void getGroupsFromAllGroups(List* groupsList, List*groupsListInput);

// Generic compare
int compare(List * list, int (*customCompare)(const void* first,const void* second), const void* searchRecord);

//Specifc compare functoin
int compareRectanglesAreaFunc(const void* first,const void* second);
int compareCirclesAreaFunc(const void* first,const void* second);
int comparePathsMain(List * list, const char * searchRecord);
int comparePathsDataFunc(char * first, const char * second);
int compareGroupsLenFunc(const void* first,const void* second);

//Adds the length for a group
int sumAllGroupsWithLen(List * list, int searchLength);
int getGroupLen(void* theGroup);

// Adds the number of attributes
int sumAllAttr(const SVG* img);

//Dummy delete for create for when calling get**FromNode
void dummyDelete(void*d);

#endif
