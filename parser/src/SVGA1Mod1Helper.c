// Name: Dawoud Husain
// ID: 1146816

#include "SVGA1Helpers.h"
#include "SVGParser.h"

// Citation: Parts of the functions in the file was taken from the CIS2750 libXmlExample.c authored by Dodji Seketeli

Rectangle *getRectFromSingleNode(xmlNode *a_node) {
    xmlNode *cur_node = a_node;
    xmlAttr *attr;

    cur_node = a_node;
    Rectangle *tmpRectangle = (Rectangle *)calloc(1, sizeof(Rectangle) + 100000);
    List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

    for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);

        if (strcmp(attrName, "x") == 0) {
            tmpRectangle->x = strtof(cont, NULL);

            int index = 0;
            char *tempPointer;
            for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                if (isalpha(*tempPointer)) {
                    tmpRectangle->units[index] = *tempPointer;
                    index++;
                }

                else {
                    strcpy(tmpRectangle->units, "");
                }
            }
        }

        else if (strcmp(attrName, "y") == 0) {
            tmpRectangle->y = strtof(cont, NULL);
        }

        else if (strcmp(attrName, "width") == 0) {
            tmpRectangle->width = strtof(cont, NULL);

        }

        else if (strcmp(attrName, "height") == 0) {
            tmpRectangle->height = strtof(cont, NULL);

        }

        else {
            Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
            tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
            strcpy(tmpAttribute->name, attrName);
            allocateFlexArray(cont, tmpAttribute->value);
            insertBack(attributeList, (void *)tmpAttribute);
        }
    }

    tmpRectangle->otherAttributes = attributeList;

    return tmpRectangle;
}

Circle *getCircleFromSingleNode(xmlNode *a_node) {
    xmlNode *cur_node = a_node;
    xmlAttr *attr;

    Circle *tmpCircle = (Circle *)calloc(1, sizeof(Circle) + 100000);
    List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

    for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);

        if (strcmp(attrName, "cx") == 0) {
            tmpCircle->cx = strtof(cont, NULL);

            int index = 0;
            char *tempPointer;
            for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                if (isalpha(*tempPointer)) {
                    tmpCircle->units[index] = *tempPointer;
                    index++;
                }

                else {
                    strcpy(tmpCircle->units, "");
                }
            }
        }

        else if (strcmp(attrName, "cy") == 0) {
            tmpCircle->cy = strtof(cont, NULL);
        }

        else if (strcmp(attrName, "r") == 0) {
            tmpCircle->r = strtof(cont, NULL);

        }

        else {
            Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
            tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
            strcpy(tmpAttribute->name, attrName);
            allocateFlexArray(cont, tmpAttribute->value);
            insertBack(attributeList, (void *)tmpAttribute);
        }
    }

    tmpCircle->otherAttributes = attributeList;
    return tmpCircle;
}

Path *getPathFromSingleNode(xmlNode *a_node) {
    xmlNode *cur_node = a_node;

    xmlAttr *attr;

    Path *tmpPath = (Path *)calloc(10000, sizeof(Path) + 10000);
    List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

    for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        // char *cont = malloc(10000000);
        char *cont = (char *)(value->content);

        if (strcmp(attrName, "d") == 0) {
            int index = 0;
            char *tempPointer;
            for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                tmpPath->data[index] = *tempPointer;
                index++;
            }
        }

        else {
            Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
            tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
            strcpy(tmpAttribute->name, attrName);
            allocateFlexArray(cont, tmpAttribute->value);
            insertBack(attributeList, (void *)tmpAttribute);
        }
    }

    tmpPath->otherAttributes = attributeList;
    return tmpPath;
}

Group *getGroupFromSingleNode(xmlNode *a_node) {
    xmlNode *cur_node = a_node;
    xmlAttr *attr;

    Group *tmpGroup = (Group *)calloc(sizeof(Group) + 100000, 1);

    List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    List *rectsList = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    List *circlesList = initializeList(&circleToString, &deleteCircle, &compareCircles);
    List *pathsList = initializeList(&pathToString, &deletePath, &comparePaths);
    List *subGroupList = initializeList(&groupToString, &deleteGroup, &compareGroups);

    for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;
        char *cont = (char *)(value->content);
        // Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
        Attribute *tmpAttribute = (Attribute *)calloc(1000, sizeof(Attribute) + 100000);
        tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
        strcpy(tmpAttribute->name, attrName);
        allocateFlexArray(cont, tmpAttribute->value);
        insertBack(attributeList, (void *)tmpAttribute);
    }

    cur_node = cur_node->children;

    for (cur_node = cur_node->next; cur_node->next != NULL; cur_node = cur_node->next) {
        if (strcmp((char *)(cur_node->name), "g") == 0) {
            Group *tmpGroup = getGroupFromSingleNode(cur_node);
            insertBack(subGroupList, (void *)tmpGroup);
        }

        else if (strcmp((char *)(cur_node->name), "rect") == 0) {
            Rectangle *tmpRectangle = getRectFromSingleNode(cur_node);
            insertBack(rectsList, (void *)tmpRectangle);
        }

        else if (strcmp((char *)(cur_node->name), "circle") == 0) {
            Circle *tmpCircle = getCircleFromSingleNode(cur_node);
            insertBack(circlesList, (void *)tmpCircle);
        }

        else if (strcmp((char *)(cur_node->name), "path") == 0) {
            Path *tmpPath = getPathFromSingleNode(cur_node);
            insertBack(pathsList, (void *)tmpPath);
        }
    }

    tmpGroup->rectangles = rectsList;
    tmpGroup->circles = circlesList;
    tmpGroup->paths = pathsList;
    tmpGroup->groups = subGroupList;
    tmpGroup->otherAttributes = attributeList;

    return tmpGroup;
}

List *getRectsFromNode(xmlNode *a_node, List *rectsList) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "g") == 0) {
                cur_node = cur_node->next;
            }

            if (strcmp((char *)(cur_node->name), "rect") == 0) {
                xmlAttr *attr;
                Rectangle *tmpRectangle = (Rectangle *)calloc(1, sizeof(Rectangle) + 100000);
                List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

                for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);

                    if (strcmp(attrName, "x") == 0) {
                        tmpRectangle->x = strtof(cont, NULL);
                        int index = 0;
                        char *tempPointer;
                        for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                            if (isalpha(*tempPointer)) {
                                tmpRectangle->units[index] = *tempPointer;
                                index++;
                            }

                            else {
                                strcpy(tmpRectangle->units, "");
                            }
                        }
                    }

                    else if (strcmp(attrName, "y") == 0) {
                        tmpRectangle->y = strtof(cont, NULL);
                    }

                    else if (strcmp(attrName, "width") == 0) {
                        tmpRectangle->width = strtof(cont, NULL);

                    }

                    else if (strcmp(attrName, "height") == 0) {
                        tmpRectangle->height = strtof(cont, NULL);

                    }

                    else {
                        Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
                        tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                        strcpy(tmpAttribute->name, attrName);
                        allocateFlexArray(cont, tmpAttribute->value);
                        insertBack(attributeList, (void *)tmpAttribute);
                    }
                }

                tmpRectangle->otherAttributes = attributeList;
                insertBack(rectsList, (void *)tmpRectangle);
            }
        }

        getRectsFromNode(cur_node->children, rectsList);
    }

    return rectsList;
}

List *getCirclesFromNode(xmlNode *a_node, List *circlesList) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "g") == 0) {
                cur_node = cur_node->next;
            }

            if (strcmp((char *)(cur_node->name), "circle") == 0) {
                xmlAttr *attr;
                Circle *tmpCircle = (Circle *)calloc(1, sizeof(Circle) + 100000);
                List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

                for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);

                    if (strcmp(attrName, "cx") == 0) {
                        tmpCircle->cx = strtof(cont, NULL);

                        int index = 0;
                        char *tempPointer;
                        for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                            if (isalpha(*tempPointer)) {
                                tmpCircle->units[index] = *tempPointer;
                                index++;
                            } else {
                                strcpy(tmpCircle->units, "");
                            }
                        }
                    }

                    else if (strcmp(attrName, "cy") == 0) {
                        tmpCircle->cy = strtof(cont, NULL);
                    }

                    else if (strcmp(attrName, "r") == 0) {
                        tmpCircle->r = strtof(cont, NULL);

                    }

                    else {
                        Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
                        tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                        strcpy(tmpAttribute->name, attrName);
                        allocateFlexArray(cont, tmpAttribute->value);
                        insertBack(attributeList, (void *)tmpAttribute);
                    }
                }

                tmpCircle->otherAttributes = attributeList;
                insertBack(circlesList, (void *)tmpCircle);
            }
        }

        getCirclesFromNode(cur_node->children, circlesList);
    }

    return circlesList;
}

List *getPathsFromNode(xmlNode *a_node, List *pathsList) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "g") == 0) {
                cur_node = cur_node->next;
            }

            if (strcmp((char *)(cur_node->name), "path") == 0) {
                xmlAttr *attr;

                Path *tmpPath = (Path *)calloc(1, sizeof(Path) + 100000);

                List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

                for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);

                    if (strcmp(attrName, "d") == 0) {
                        allocateFlexArray(cont, (tmpPath->data));
                    }

                    else {
                        Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);

                        tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                        strcpy(tmpAttribute->name, attrName);
                        allocateFlexArray(cont, tmpAttribute->value);
                        insertBack(attributeList, (void *)tmpAttribute);
                    }
                }

                tmpPath->otherAttributes = attributeList;
                insertBack(pathsList, (void *)tmpPath);
            }
        }

        getPathsFromNode(cur_node->children, pathsList);
    }

    return pathsList;
}

List *getOtherAttributesFromNode(xmlNode *a_node, List *attributeList) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "g") == 0) {
                cur_node = cur_node->next;
            }

            if (strcmp((char *)(cur_node->name), "svg") == 0) {
                xmlAttr *attr;

                for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);
                    Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
                    tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                    strcpy(tmpAttribute->name, attrName);
                    allocateFlexArray(cont, tmpAttribute->value);
                    insertBack(attributeList, (void *)tmpAttribute);
                }
            }
        }

        getOtherAttributesFromNode(cur_node->children, attributeList);
    }

    return attributeList;
}

List *getGroupsFromNode(xmlNode *a_node, List *groupsList) {
    xmlNode *cur_node = NULL;
    xmlNode *nextNode = a_node;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "g") == 0) {
                xmlAttr *attr;

                Group *tmpGroup = (Group *)calloc(sizeof(Group), 1);

                List *attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                List *rectsList = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
                List *circlesList = initializeList(&circleToString, &deleteCircle, &compareCircles);
                List *pathsList = initializeList(&pathToString, &deletePath, &comparePaths);
                List *subGroupList = initializeList(&groupToString, &deleteGroup, &compareGroups);

                for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);

                    Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
                    tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                    strcpy(tmpAttribute->name, attrName);
                    allocateFlexArray(cont, tmpAttribute->value);
                    insertBack(attributeList, (void *)tmpAttribute);
                }

                nextNode = cur_node->next;
                cur_node = cur_node->children;

                for (cur_node = cur_node->next; cur_node->next != NULL; cur_node = cur_node->next) {
                    if (strcmp((char *)(cur_node->name), "rect") == 0) {
                        Rectangle *tmpRectangle = getRectFromSingleNode(cur_node);
                        insertBack(rectsList, (void *)tmpRectangle);
                    }

                    else if (strcmp((char *)(cur_node->name), "circle") == 0) {
                        Circle *tmpCircle = getCircleFromSingleNode(cur_node);
                        insertBack(circlesList, (void *)tmpCircle);
                    }

                    else if (strcmp((char *)(cur_node->name), "path") == 0) {
                        Path *tmpPath = getPathFromSingleNode(cur_node);
                        insertBack(pathsList, (void *)tmpPath);
                    }

                    else if (strcmp((char *)(cur_node->name), "g") == 0) {
                        Group *tmpGroup = getGroupFromSingleNode(cur_node);
                        insertBack(subGroupList, (void *)tmpGroup);
                    }

                    // Other Acctributes
                    else {
                        for (attr = cur_node->properties; attr != NULL; attr = attr->next) {
                            xmlNode *value = attr->children;
                            char *attrName = (char *)attr->name;
                            char *cont = (char *)(value->content);

                            Attribute *tmpAttribute = (Attribute *)calloc(sizeof(Attribute) + 100000, 1);
                            tmpAttribute->name = (char *)calloc(sizeof(char) * 10000, 1);
                            strcpy(tmpAttribute->name, attrName);
                            allocateFlexArray(cont, tmpAttribute->value);
                            insertBack(attributeList, (void *)tmpAttribute);
                        }
                    }
                }

                tmpGroup->rectangles = rectsList;
                tmpGroup->circles = circlesList;
                tmpGroup->paths = pathsList;
                tmpGroup->groups = subGroupList;
                tmpGroup->otherAttributes = attributeList;

                insertBack(groupsList, (void *)tmpGroup);

                cur_node = nextNode;
            }
        }

        getGroupsFromNode(nextNode->children, groupsList);
    }

    return groupsList;
}

void getNameSpace(xmlNode *a_node, char namespace[256]) {
    strcpy(namespace, "");
    strcpy(namespace, (char *)(a_node->ns->href));
    return;
}

void getTitle(xmlNode *a_node, char title[256]) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "title") == 0) {
                if (cur_node->children->content != NULL && strcmp((char *)(cur_node->children->content), "") != 0) {
                    strcpy(title, (char *)(cur_node->children->content));
                }
            }
        }
        getTitle(cur_node->children, title);
    }

    return;
}

void getDescription(xmlNode *a_node, char description[256]) {
    xmlNode *cur_node = NULL;

    if (description[0] == '\0') {
        strcpy(description, "");
    }

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)(cur_node->name), "desc") == 0) {
                if (cur_node->children->content != NULL) {
                    strcpy(description, (char *)(cur_node->children->content));
                }
            }
        }

        getDescription(cur_node->children, description);
    }

    return;
}