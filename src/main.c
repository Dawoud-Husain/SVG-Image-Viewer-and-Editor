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

    
    strcat(tmpStr, "**************************************Circles******************************* \n");
    while ((elem = nextElement(&iter1)) != NULL){
        Circle* tmpCircle = (Circle*)elem;
        char* str = circleToString(tmpCircle);

        strcat(tmpStr, "Circle \n");
        strcat(tmpStr,str);
        strcat(tmpStr, "\n");
        free(str);
    }



    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
    printf("%s", tmpStr);


   deleteSVG(mySVG);



    
    return 0;
}