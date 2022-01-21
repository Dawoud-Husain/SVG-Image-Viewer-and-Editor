
#include "SVGParser.h"
#include "SVGAdditionalHelper.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <libxml/parser.h>
#include <libxml/tree.h>


List* getRectsFromNode(xmlNode * a_node, List* rectsList){
    
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next){
        if (cur_node->type == XML_ELEMENT_NODE) {
            if(strcmp((char *)(cur_node->name), "rect") == 0){
                xmlAttr *attr;
                 Rectangle * tmpRectangle = (Rectangle*)malloc(sizeof(Rectangle));
                 List* attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                 
                for (attr = cur_node->properties; attr != NULL; attr = attr->next){
                        xmlNode *value = attr->children;
                        char *attrName = (char *)attr->name;
                        char *cont = (char *)(value->content);

                        //printf("\tattribute name: %s, attribute value = %s\n", attrName, cont);
            
                        if(strcmp(attrName, "x") == 0){
                            tmpRectangle->x = strtof(cont, NULL);
                            
                            int index = 0;
                            char * tempPointer;
                            for (tempPointer = cont; *tempPointer != '\0'; tempPointer++) {
                                if(isalpha(*tempPointer)){
                                    tmpRectangle->units[index] = *tempPointer;
                                    index ++;
                                }
                            }
                        }

                        else if(strcmp(attrName, "y") == 0){
                            tmpRectangle->y =  strtof(cont, NULL);
                        }
                        
                        else if(strcmp(attrName, "width") == 0){
                            if(strtof(cont, NULL) >= 0){
                                 tmpRectangle->width =  strtof(cont, NULL);
                            }
                        }

                         else if(strcmp(attrName, "height") == 0){
                            if(strtof(cont, NULL) >= 0){
                                tmpRectangle->height =  strtof(cont, NULL);
                            }        
                        }   

                        else{
                            Attribute * tmpAttribute = (Attribute*)malloc(sizeof(Attribute));

                            tmpAttribute->name = attrName;

                            char valueArray[strlen(cont) + 1];
                            strcpy(valueArray, cont);

                            strcpy(tmpAttribute->value,valueArray);
                             
                            insertBack(attributeList, (void*)tmpAttribute);
                        }
                  }

                  tmpRectangle->otherAttributes = attributeList;
                  insertBack(rectsList, (void*)tmpRectangle);
            }
        }

        getRectsFromNode(cur_node->children, rectsList);
    }

    return rectsList;
}

List* getCirclesFromNode(xmlNode * a_node){
    List* circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    return circles;
}
List* getGroupsFromNode(xmlNode * a_node){
    List* groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
    return groups;
}

List* getPathsFromNode(xmlNode * a_node){
    List* paths = initializeList(&pathToString, &deletePath, &comparePaths);
    return paths;
}

List* getOtherAttributesFromNode(xmlNode * a_node, List* attributeList){
      
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next){
        if (cur_node->type == XML_ELEMENT_NODE) {
            if(strcmp((char *)(cur_node->name), "svg") == 0){
                xmlAttr *attr;
                   
                 //List* attributeList = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                 
                for (attr = cur_node->properties; attr != NULL; attr = attr->next){
                    xmlNode *value = attr->children;
                    char *attrName = (char *)attr->name;
                    char *cont = (char *)(value->content);

                    Attribute * tmpAttribute = (Attribute*)malloc(sizeof(Attribute));

                    tmpAttribute->name = attrName;

                    char valueArray[strlen(cont) + 1];
                    strcpy(valueArray, cont);

                    strcpy(tmpAttribute->value,valueArray);

                    // printf("%s %s", tmpAttribute->name, tmpAttribute->value);
                        
                    insertBack(attributeList, (void*)tmpAttribute);
                }
            }
        }

        getOtherAttributesFromNode(cur_node->children, attributeList);
    }

    return attributeList;
}



void  getNameSpace(xmlNode * a_node, char namespace[256]){
    // return a_node->ns->href ;
    strcpy(namespace, (char *)(a_node->ns->href));
    return;
}

void getTitle(xmlNode * a_node, char title[256]){

    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            // printf("%s %s\n", cur_node->name, cur_node->content);
            // printf("node type: Element, name: %s\n", cur_node->name);
            if(strcmp((char *)(cur_node->name), "title") == 0){
                // printf("content: %s\n", cur_node->children->content);

                if (cur_node->children->content != NULL && strcmp((char *)(cur_node->children->content), "") != 0){
                    strcat(title,(char *)(cur_node->children->content));
                }
            }
        }
        getTitle(cur_node->children, title );
    }

    return;
}

void getDescription(xmlNode * a_node, char description[256]){
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            // printf("%s %s\n", cur_node->name, cur_node->content);
            // printf("node type: Element, name: %s\n", cur_node->name);
            if(strcmp((char *)(cur_node->name), "desc") == 0){
                // printf("content: %s\n", cur_node->children->content);

                if (cur_node->children->content != NULL){
        
                    strcat(description, (char *)(cur_node->children->content)); 
                }
            }
        }

        getDescription(cur_node->children, description );
    }
    return;
}


int validateXML(const char *filename) {
    xmlParserCtxtPtr ctxt; /* the parser context */
    xmlDocPtr doc; /* the resulting document tree */

    /* create a parser context */
    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
        ///fprintf(stderr, "Failed to allocate parser context\n");
	    return -1;
    }
    /* parse the file, activating the DTD validation option */
    doc = xmlCtxtReadFile(ctxt, filename, NULL, XML_PARSE_DTDVALID);

    /* check if parsing succeeded */
    if (doc == NULL) {
        //fprintf(stderr, "Failed to parse %s\n", filename);
        return -1;
    } 
    
    else {
        /* check if validation succeeded */
        if (ctxt->valid == 0){
            //fprintf(stderr, "Failed to validate %s\n", filename);
            return -1;
        }
        
        /* free up the resulting document */
        xmlFreeDoc(doc);
    }

    /* free up the parser context */
    xmlFreeParserCtxt(ctxt);
    return 1;
}

