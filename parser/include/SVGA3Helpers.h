//******************************************MOD 3 ***********************************************************

char* createSVGFromJSON();

bool isValidSVGFromFile(const char* filename, const char* schemaFile);

int getFileSize(const char* filename);

char* getSVGDescription(const char* filename, const char* schemaFile);

char* getRectsImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getCirclesImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getPathsImmediateChildrenSummary(const char* filename, const char* schemaFile);

char* getGroupsImmediateChildrenSummary(const char* filename, const char* schemaFile);

bool updateSVGNameDesc(const char* filename, const char* schemaFile,  const char* newTitle ,const char* newDesc);