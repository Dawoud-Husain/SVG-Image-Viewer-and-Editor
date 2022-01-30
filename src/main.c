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

    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MODULE 2||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
    printf("%s\n\n", tmpStr);


   deleteSVG(mySVG);



    
    return 0;
}