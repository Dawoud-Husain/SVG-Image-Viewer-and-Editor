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


    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MODULE 2||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
    printf("%s\n\n", tmpStr);


   deleteSVG(mySVG);



    
    return 0;
}