// Name: Dawoud Husain
// ID: 1146816


#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "SVGParser.h"



int main(int argc, char **argv)
{
    if (argc != 2){
        return(1);
    }

   SVG* mySVG = createSVG(argv[1]);

   char * string = SVGToString(mySVG);
   printf("%s", string);
   free(string);


    char tmpStr[1000000];
    strcpy(tmpStr, "");

    void* elem;
    List * rectsList = getRects(mySVG);
    ListIterator iter1 = createIterator(rectsList);

    strcat(tmpStr, "**************************************Rectangles******************************* \n");
    while ((elem = nextElement(&iter1)) != NULL){
        Rectangle* tmpRectangle = (Rectangle*)elem;
        char* str = rectangleToString(tmpRectangle);

        strcat(tmpStr, "Rectangle \n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
        free(str);
       
    }

     freeList(rectsList);


    
    void* elem2;
    List * circlesList = getCircles(mySVG);
    ListIterator iter2 = createIterator(circlesList);

    strcat(tmpStr, "**************************************Circles******************************* \n");
    while ((elem2 = nextElement(&iter2)) != NULL){
        Circle* tmpCircle = (Circle*)elem2;
        char* str = circleToString(tmpCircle);

        strcat(tmpStr, "Circle \n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
        free(str);
    }

    freeList(circlesList);


        
    void* elem3;
    List * pathsList = getPaths(mySVG);
    ListIterator iter3 = createIterator(pathsList);

    strcat(tmpStr, "**************************************Paths******************************* \n");
    while ((elem3 = nextElement(&iter3)) != NULL){
        Path* tmpPath = (Path*)elem3;
        char* str = pathToString(tmpPath);

        strcat(tmpStr, "Path \n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
        free(str);
    }

    freeList(pathsList);

    void* elem4;
    List * groupsList = getGroups(mySVG);
    ListIterator iter4 = createIterator(groupsList);

    strcat(tmpStr, "**************************************Groups******************************* \n");
    while ((elem4 = nextElement(&iter4)) != NULL){
        Group* tmpGroup = (Group*)elem4;
        char* str = groupToString(tmpGroup);

        strcat(tmpStr, "Group \n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
        free(str);
    }

    freeList(groupsList);


    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MODULE 2||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
    printf("%s\n\n", tmpStr);


    printf("Num Rects with area 0 is: %d expected 0\n", numRectsWithArea(mySVG, 0.0));
    printf("Num Rects with area 716404 is: %d expected 1\n", numRectsWithArea(mySVG, 716404.0));
    
    printf("Num Circles with area 0 is: %d expected 0\n", numCirclesWithArea(mySVG, 0.0));
    printf("Num Circles with area 314.16 is: %d expected 5\n", numCirclesWithArea(mySVG, 314.16));
    
    printf("Num Paths with data safdsagfag is: %d expected 0\n", numPathsWithdata(mySVG, "safdsagfag"));
    printf("Num Paths with data M200,300 Q400,50 600,300 T1000,300 is: %d expected 1\n", numPathsWithdata(mySVG, "M200,300 Q400,50 600,300 T1000,300"));

    printf("Num Groups with Len 0 is: %d expected 0\n", numGroupsWithLen(mySVG, 0));
    printf("Num Groups with Len 2: %d expected 1\n", numGroupsWithLen(mySVG, 2));

    
    printf("The number of attribtues is %d expected 9\n", numAttr(mySVG));
  

   deleteSVG(mySVG);
    
    return 0;
}