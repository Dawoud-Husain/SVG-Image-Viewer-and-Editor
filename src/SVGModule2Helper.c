// Name: Dawoud Husain
// ID: 1146816
    
#include "SVGParser.h"
#include "SVGAdditionalHelper.h"

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>



void* compare(List * list, int (*customCompare)(const void* first,const void* second), const void* searchRecord){
	if (customCompare == NULL)
		return NULL;

	ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{
		if (customCompare(data, searchRecord))
			return data;

		data = nextElement(&itr);
	}

	return NULL;
}

int compareRectanglesAreaFunc(const void* first,const void* second){
	
	return 0;
}


void getRectsFromAllGroups(List* rectsList, List*groupsList){

    ListIterator iter = createIterator(groupsList);
    void*groupElement;
    while ((groupElement = nextElement(&iter)) != NULL){
        Group* tmpGroup = (Group*)groupElement;
        
        ListIterator rectIter = createIterator(tmpGroup->rectangles);
        void* rectangleElement;
        while ((rectangleElement = nextElement(&rectIter)) != NULL){
            Rectangle* tmpRectangle = (Rectangle*)rectangleElement;
            insertBack(rectsList, (void*)tmpRectangle);
        }

        if ((tmpGroup->groups->length) > 0){
            getRectsFromAllGroups(rectsList, tmpGroup->groups);
        }
    }
} 


void getCirclesFromAllGroups(List* circlesList, List*groupsList){
     
    ListIterator iter = createIterator(groupsList);
    void*groupElement;

    while ((groupElement = nextElement(&iter)) != NULL){
        Group* tmpGroup = (Group*)groupElement;
        ListIterator circleIter = createIterator(tmpGroup->circles);
        void* circleElement;

        while ((circleElement = nextElement(&circleIter)) != NULL){
            Circle* tmpCircle = (Circle*)circleElement;
            insertBack(circlesList, (void*)tmpCircle);    
        }
       
        if ((tmpGroup->groups->length) > 0){
            getCirclesFromAllGroups(circlesList, tmpGroup->groups);
        }
    }
}


void getPathsFromAllGroups(List* pathsList, List*groupsList){
     
    ListIterator iter = createIterator(groupsList);
    void*groupElement;

    while ((groupElement = nextElement(&iter)) != NULL){
        Group* tmpGroup = (Group*)groupElement;
        ListIterator pathIter = createIterator(tmpGroup->paths);
        void* pathElement;

        while ((pathElement = nextElement(&pathIter)) != NULL){
            Path* tmpPath = (Path*)pathElement;
            insertBack(pathsList, (void*)tmpPath);    
        }
       
        if ((tmpGroup->groups->length) > 0){
            getPathsFromAllGroups(pathsList, tmpGroup->groups);
        }
    }
}

void getGroupsFromAllGroups(List* groupsList, List*groupsListInput){
     
    ListIterator iter = createIterator(groupsListInput);
    void*groupElement;

    while ((groupElement = nextElement(&iter)) != NULL){
        Group* tmpGroup = (Group*)groupElement;
        ListIterator groupIter = createIterator(tmpGroup->groups);
        void* groupElement;

        while ((groupElement = nextElement(&groupIter)) != NULL){
            Group* tmpGroup = (Group*)groupElement;
            insertBack(groupsList, (void*)tmpGroup);    
        }
       
        if ((tmpGroup->groups->length) > 0){
            getGroupsFromAllGroups(groupsList, tmpGroup->groups);
        }
    }
}

