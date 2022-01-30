#ifndef SVGADDITIONALHELPER_H
#define SVGADDITIONALHELPER_H

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"


void allocateFlexArray(char str[], char* src);

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

#endif
