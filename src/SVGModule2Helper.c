// Name: Dawoud Husain
// ID: 1146816
    
#include "SVGParser.h"
#include "SVGAdditionalHelper.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
 
#include <libxml/parser.h>
#include <libxml/tree.h>


int compare(List * list, int (*customCompare)(const void* first,const void* second), const void* searchRecord){
	if (customCompare == NULL)
		return -1;

    
	ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{
        printf("!!!!!!!!!!!!!!!!!!\n\n");
		if (customCompare(data, searchRecord) == 1){
            return 1;
        }

		data = nextElement(&itr);
	}

  

	return 0;
}

int compareRectanglesAreaFunc(const void* first,const void* second){
      
    Rectangle* tmpRectangle = (Rectangle*)first;

    float rectangleArea = tmpRectangle->width * tmpRectangle->height;
    rectangleArea = ceil(rectangleArea);

    float secondData = *((float *)second);
    secondData = ceil(secondData);

     printf("%f %f", rectangleArea, secondData);
     
    if(rectangleArea == secondData){
        return 1;
    }

	return 0;
}


int compareRectanglesAreaFunc(const void* first,const void* second){
       Circle* tmpCircle = (Circle*)first;

    float cricleArea = tmpRectangle->width * tmpRectangle->height;
    rectangleArea = ceil(rectangleArea);

    float secondData = *((float *)second);
    secondData = ceil(secondData);

     printf("%f %f", rectangleArea, secondData);
     
    if(rectangleArea == secondData){
        return 1;
    }

	return 0;
}
int compareCirclesAreaFunc(const void* first,const void* second);
int comparePathsDataFunc(const void* first,const void* second);
int compareGroupsLenFunc(const void* first,const void* second);



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

