#ifndef SVGADDITIONALHELPER_H
#define SVGADDITIONALHELPER_H

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"

// Utility Functions
void allocateFlexArray(char str[], char* src);

// Module 1 Helper Functions
void  getNameSpace(xmlNode * a_node, char namespace[256]);

void getTitle(xmlNode * a_node, char title[256]);
void getDescription(xmlNode * a_node, char description[256]);

List* getRectsFromNode(xmlNode * a_node, List* rectsList);
List* getCirclesFromNode(xmlNode * a_node, List * circlesList);
List* getGroupsFromNode(xmlNode * a_node, List* groupsList);
List* getPathsFromNode(xmlNode * a_node, List* pathsList);
List* getOtherAttributesFromNode(xmlNode * a_node, List* attributeList);

Rectangle * getRectFromSingleNode(xmlNode * a_node);
Circle * getCircleFromSingleNode(xmlNode * a_node);
Path * getPathFromSingleNode(xmlNode * a_node);
Group * getGroupFromSingleNode(xmlNode * a_node);


// Module 2 Helper Functions
void getRectsFromAllGroups(List* rectsList, List*groupsList);
void getCirclesFromAllGroups(List* circlesList, List*groupsList);
void getPathsFromAllGroups(List* circlesList, List*groupsList);
void getGroupsFromAllGroups(List* groupsList, List*groupsListInput);

int compare(List * list, int (*customCompare)(const void* first,const void* second), const void* searchRecord);
int compareRectanglesAreaFunc(const void* first,const void* second);
int compareCirclesAreaFunc(const void* first,const void* second);


int comparePathsMain(List * list, const char * searchRecord);
int comparePathsDataFunc(char * first, const char * second);

int compareGroupsLenFunc(const void* first,const void* second);


int sumAllGroupsWithLen(List * list, int searchLength);
int getGroupLen(void* theGroup);

int sumAllAttr(const SVG* img);

void dummyDelete(void*d);

#endif
