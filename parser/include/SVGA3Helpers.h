#ifndef SVGA3ADDITIONALHELPER_H
#define SVGA3ADDITIONALHELPER_H

//******************************************MOD 3 ***********************************************************

char* createSVGFromJSON();

bool isValidSVGFromFile(const char* filename, const char* schemaFile);

int getFileSize(const char* filename);

char* getSVGTitle(const char* filename, const char* schemaFile);
char* getSVGDescription(const char* filename, const char* schemaFile);

char* getRectsImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getCirclesImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getPathsImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getGroupsImmediateChildrenSummary(const char* filename, const char* schemaFile);

bool updateSVGNameDesc(const char* filename, const char* schemaFile, const char* newTitle, const char* newDesc);


char* covertAttrListToJSONA3(const List* list);


char* convertrectListToJSONA3(const List* list);
char* getRectsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile);


char* convertcircListToJSONA3(const List* list);
char* getCircsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* convertpathListToJSONA3(const List* list);
char* getPathsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* convertGroupListToJSONA3(const List* list);
char* getGroupsAttrImmediateChildrenSummary(const char* filename, const char* schemaFile);

bool addRect(const char* filename, const char* schemaFile, float theX, float theY, float theWidth, float theHeight);
bool addCirc(const char* filename, const char* schemaFile, float theCX, float theCY, float theR);

#endif
