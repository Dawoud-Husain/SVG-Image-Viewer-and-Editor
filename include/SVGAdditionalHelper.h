#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"


int validateXML(const char* fileName);

void  getNameSpace(xmlNode * a_node, char namespace[256]);

void getTitle(xmlNode * a_node, char title[256]);
void getDescription(xmlNode * a_node, char description[256]);



List* getRectsFromNode(xmlNode * a_node, List* rectsList);
List* getCirclesFromNode(xmlNode * a_node, List * circlesList);
List* getGroupsFromNode(xmlNode * a_node);
List* getPathsFromNode(xmlNode * a_node);
List* getOtherAttributesFromNode(xmlNode * a_node, List* attributeList);