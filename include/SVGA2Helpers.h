#ifndef SVGA2ADDITIONALHELPER_H
#define SVGA2ADDITIONALHELPER_H

// Citation: author:  Lucas Brasilino <brasilino@recife.pe.gov.br>
// From: http://www.xmlsoft.org/html/libxml-tree.html
bool covertSVGTOXMLTree(const SVG* img, const char* fileName);

void getGroupForTree(xmlNodePtr parentNode, void* data, char buff[1000000], char buff2[1000000]);

// Citation: author: Sam
// From: https :  // knol2share.blogspot.com/2009/05/validate-xml-against-xsd-in-c.html
bool validateXMLTREE(const char* xmlFile, const char* schemaFile);

bool validateSVGStruct(const SVG* img);

bool validateAttr(Attribute* tmpAttribute);

bool validateRect(Rectangle* tmpRectangle);

bool validateCircle(Circle* tmpCircle);

bool validatePath(Path* tmpPath);
bool validateGroup(Group* tmpGroup);

bool updateElement(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);

bool updateSVGAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);
bool updateSVGRectAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);
bool updateSVGCircleAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);
bool updateSVGPathAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);
bool updateSVGGroupAttr(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute);
bool isValidUnit(char* unit);

#endif