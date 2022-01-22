// Name: Dawoud Husain
// ID: 1146816
    
#include "SVGParser.h"
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void deleteAttribute( void* data){
    Attribute* tmpAttribute;
	
	if (data == NULL){
		return;
	}
	
	tmpAttribute = (Attribute*)data;
    // free(tmpAttribute->name);
	free(tmpAttribute);
}

char* attributeToString(void* data){
    char* tmpStr;
	Attribute* tmpAttribute;
	int len;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpAttribute = (Attribute*)data;
		
	//len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
    len = 100000;
	tmpStr = (char*)malloc(sizeof(char)*len);
	

	sprintf(tmpStr, "Name: %s Value:%s", tmpAttribute->name, tmpAttribute->value); //Problem?

	return tmpStr;
}

int compareAttributes(const void *first, const void *second){
    return 0;
}

void deleteGroup(void* data){
    return;
}
char* groupToString(void* data){
     char* groupToString = "";
    return groupToString;
}
int compareGroups(const void *first, const void *second){
    return 0;
}


void deleteRectangle(void* data){
   Rectangle* tmpRectangle;
	
	if (data == NULL){
		return;
	}
	
	tmpRectangle = (Rectangle*)data;
	
	//free(tmpRectangle->otherAttributes);
    freeList(tmpRectangle->otherAttributes);	
	free(tmpRectangle);
}   

char* rectangleToString(void* data){
    char* tmpStr;
	Rectangle* tmpRectangle;
	int len;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpRectangle = (Rectangle*)data;
		
	//len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
    len = 100000;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "x: %f y:%f width:%f height:%f unit: %s\n", tmpRectangle->x, tmpRectangle->y, tmpRectangle->width, tmpRectangle->height, tmpRectangle->units);

    void* elem;

    ListIterator iter = createIterator(tmpRectangle->otherAttributes);
	while ((elem = nextElement(&iter)) != NULL){
		Attribute* tmpAttribute = (Attribute*)elem;
		char* str = attributeToString(tmpAttribute);

        strcat(tmpStr, "Rectangle Attribute\n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
		free(str);
	}

	return tmpStr;
}

int compareRectangles(const void *first, const void *second){
    return 0;
}

void deleteCircle(void* data){
     Circle* tmpcircle;
	
	if (data == NULL){
		return;
	}
	
	tmpcircle = (Circle*)data;
	
	//free(tmpcircle->otherAttributes);
    freeList(tmpcircle->otherAttributes);	
	free(tmpcircle);
}

char* circleToString(void* data){
    char* tmpStr;
	Circle* tmpCircle;
	int len;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpCircle = (Circle*)data;
		
	//len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
    len = 100000;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "cx: %f cy:%f r:%f unit: %s\n", tmpCircle->cx, tmpCircle->cy, tmpCircle->r, tmpCircle->units);

    void* elem;

    ListIterator iter = createIterator(tmpCircle->otherAttributes);
	while ((elem = nextElement(&iter)) != NULL){
		Attribute* tmpAttribute = (Attribute*)elem;
		char* str = attributeToString(tmpAttribute);

        strcat(tmpStr, "Circle Attribute\n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
		free(str);
	}

	return tmpStr;
}

int compareCircles(const void *first, const void *second){
    return 0;
}

void deletePath(void* data){
    Path* tmppath;
	
	if (data == NULL){
		return;
	}
	
	tmppath = (Path*)data;

    freeList(tmppath->otherAttributes);	
	free(tmppath);
}


char* pathToString(void* data){
   char* tmpStr;
	Path* tmpPath;
	int len;
	
	if (data == NULL){
		return NULL;
	}
	
	tmpPath = (Path*)data;
		
	//len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
    len = 10000000;
	tmpStr = (char*)malloc(sizeof(char)*len);

	sprintf(tmpStr, "data: %s\n",  tmpPath->data);

    void* elem;

    ListIterator iter = createIterator(tmpPath->otherAttributes);
	while ((elem = nextElement(&iter)) != NULL){
		Attribute* tmpAttribute = (Attribute*)elem;
		char* str = attributeToString(tmpAttribute);

        strcat(tmpStr, "Path Attribute\n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
		free(str);
	}

	return tmpStr;
}

int comparePaths(const void *first, const void *second){
    return 0;
}