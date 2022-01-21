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
   deleteSVG(mySVG);
    
    return 0;
}