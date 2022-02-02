// Name: Dawoud Husain
// ID: 1146816
    
#include "SVGParser.h"
#include "SVGHelpers.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
 
#include <libxml/parser.h>
#include <libxml/tree.h>


int sumAllAttr(const SVG* img){

    int count = 0;

    //**************************************OtherAttributes*******************************

    count += img->otherAttributes->length;
    // void* elem0;
    // List * attrList = img->otherAttributes;
    // ListIterator iter0 = createIterator(attrList);
    
    // while ((elem = nextElement(&iter0)) != NULL){
    //     Rectangle* tmpRectangle = (Rectangle*)elem;
    //     count += tmpRectangle->otherAttributes->length;
    // }


    //**************************************Rectangles*******************************
    void* elem;
    List * rectsList = getRects(img);
    ListIterator iter1 = createIterator(rectsList);
    
    while ((elem = nextElement(&iter1)) != NULL){
        Rectangle* tmpRectangle = (Rectangle*)elem;
        count += tmpRectangle->otherAttributes->length;
    }
    
    void* elem2;
    List * circlesList = getCircles(img);
    ListIterator iter2 = createIterator(circlesList);
    
    //**************************************Circles*******************************
    while ((elem2 = nextElement(&iter2)) != NULL){
        Circle* tmpCircle = (Circle*)elem2;
        count += tmpCircle->otherAttributes->length;
    }

    // **************************************Paths*******************************

    void* elem3;
    List * pathsList = getPaths(img);
    ListIterator iter3 = createIterator(pathsList);
   
    while ((elem3 = nextElement(&iter3)) != NULL){
        Path* tmpPath = (Path*)elem3;
        count += tmpPath->otherAttributes->length;     
    }

     //**************************************Groups******************************* 

    void* elem4;
    List * groupsList = getGroups(img);
    ListIterator iter4 = createIterator(groupsList);

    while ((elem4 = nextElement(&iter4)) != NULL){
        Group* tmpGroup = (Group*)elem4;
        count += tmpGroup->otherAttributes->length;
    }

    freeList(rectsList);
    freeList(circlesList);
    freeList(pathsList);
    freeList(groupsList);

    return count;
}


int sumAllGroupsWithLen(List * list, int searchLength){
    int count = 0;

    ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{

		int groupLen = getGroupLen(data);

        if(groupLen == searchLength){
            count += 1;
        }

		data = nextElement(&itr);
	}

    return count;
}


int getGroupLen(void* theGroup){

    Group* tmpGroup = (Group*)theGroup;
    int lengthGroup = 0;

    lengthGroup += tmpGroup -> rectangles -> length;
    lengthGroup += tmpGroup -> circles -> length;
    lengthGroup += tmpGroup -> paths -> length;
    lengthGroup += tmpGroup -> groups -> length;
     
    return lengthGroup;
}

int compare(List * list, int (*customCompare)(const void* first,const void* second), const void* searchRecord){
    int numMatches = 0;

	if (customCompare == NULL){
        return 0;
    }
    
	ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{

		if (customCompare(data, searchRecord) == 1){
            numMatches += 1;
        }

		data = nextElement(&itr);
	}

	return numMatches;
}

int compareRectanglesAreaFunc(const void* first,const void* second){
      
    Rectangle* tmpRectangle = (Rectangle*)first;

    float rectangleArea = tmpRectangle->width * tmpRectangle->height;
    rectangleArea = ceil(rectangleArea);

    float secondData = *((float *)second);
    secondData = ceil(secondData);

    //  printf("%f %f", rectangleArea, secondData);
     
    if(rectangleArea == secondData){
        return 1;
    }

	return 0;
}


int compareCirclesAreaFunc(const void* first,const void* second){
    Circle* tmpCircle = (Circle*)first;

    float radius =  tmpCircle->r;
    float cricleArea = 3.14159 * radius * radius;
    cricleArea = ceil(cricleArea); 

    float secondData = *((float *)second);
    secondData = ceil(secondData);

    //printf("%f %f\n", cricleArea, secondData);
     
    if(cricleArea == secondData){
        return 1;
    }

	return 0;
}



int comparePathsMain(List * list, const char * searchRecord){
    int numMatches = 0;

	ListIterator itr = createIterator(list);

	void* data = nextElement(&itr);
	while (data != NULL)
	{

		if (comparePathsDataFunc(data, searchRecord) == 1){
            numMatches += 1;
        }

		data = nextElement(&itr);
	}

	return numMatches;
}

int comparePathsDataFunc(char * first, const char * second){
    Path* tmpPath = (Path*)first;

    char * retreivedData =  tmpPath->data;
    char * secondData = (char*)second;

    // printf("%s || %s\n", retreivedData, secondData);
     
    if(strcmp(retreivedData, secondData) == 0){
        return 1;
    }

	return 0;
}

int compareGroupsLenFunc(const void* first,const void* second){

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

void dummyDelete(void*d){
    return;
}