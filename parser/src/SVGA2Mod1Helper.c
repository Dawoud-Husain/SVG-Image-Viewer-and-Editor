#include "SVGA1Helpers.h"
#include "SVGA2Helpers.h"

bool validateSVGWithSchema(const char* fileName, const char* schemaFile) {

    const char* XMLFileName = fileName;
    const char* XSDFileName = schemaFile;
    xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    int ret;

    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(XSDFileName);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    doc = xmlReadFile(XMLFileName, NULL, 0);

    if (doc == NULL) {
        return false;
    } 
    
    else {
        xmlSchemaValidCtxtPtr ctxt;

        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
        ret = xmlSchemaValidateDoc(ctxt, doc);

        if (ret == 0) {
            //Valid
        } 

        //Failed
        else if (ret > 0) {
            return false;
        } 

        //Error
        else {
            return false;
        }
        xmlSchemaFreeValidCtxt(ctxt);
        xmlFreeDoc(doc);
    }


    // Free Varibles/Parser
    if (schema != NULL){
        xmlSchemaFree(schema);
    }

    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    

    return true;
}

bool validateSVGStruct(const SVG* img) {
    if (img->title == NULL || img->description == NULL || img->namespace == NULL || strcmp(img->namespace, "") == 0) {
        return false;
    }

    if (img->otherAttributes == NULL || img->rectangles == NULL || img->circles == NULL || img->paths == NULL || img->groups == NULL) {
        return false;
    }

    void* svcAccElement;
    ListIterator accIter = createIterator(img->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;

        if (validateAttr(tmpAttribute) == false) {
            return false;
        }
    }

    void* rectangleElement;
    ListIterator iter = createIterator(img->rectangles);
    while ((rectangleElement = nextElement(&iter)) != NULL) {
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;

        if (validateRect(tmpRectangle) == false) {
            return false;
        }
    }

    void* circleElement;
    ListIterator circleIter = createIterator(img->circles);
    while ((circleElement = nextElement(&circleIter)) != NULL) {
        Circle* tmpCircle = (Circle*)circleElement;

        if (validateCircle(tmpCircle) == false) {
            return false;
        }
    }

    void* pathElement;
    ListIterator pathIter = createIterator(img->paths);
    while ((pathElement = nextElement(&pathIter)) != NULL) {
        Path* tmpPath = (Path*)pathElement;

        if (validatePath(tmpPath) == false) {
            return false;
        }
    }

    void* groupElement;
    ListIterator groupIter = createIterator(img->groups);
    while ((groupElement = nextElement(&groupIter)) != NULL) {
        Group* tmpGroup = (Group*)groupElement;

        if (validateGroup(tmpGroup) == false) {
            return false;
        }
    }

    return true;
}

bool validateAttr(Attribute* tmpAttribute) {
    if (tmpAttribute->name == NULL) {
        return false;
    }

    return true;
}

bool validateRect(Rectangle* tmpRectangle) {
    if (tmpRectangle->width < 0 || tmpRectangle->height < 0) {
        return false;
    }

    // if (isValidUnit(tmpRectangle->units) == false) {
    //     return false;
    // }

    void* svcAccElement;
    ListIterator accIter = createIterator(tmpRectangle->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;

        if (validateAttr(tmpAttribute) == false) {
            return false;
        }
    }

    return true;
}

bool validateCircle(Circle* tmpCircle) {
    if (tmpCircle->r < 0) {
        return false;
    }

    // if (isValidUnit(tmpCircle->units) == false) {
    //     return false;
    // }

    void* svcAccElement;
    ListIterator accIter = createIterator(tmpCircle->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;

        if (validateAttr(tmpAttribute) == false) {
            return false;
        }
    }

    return true;
}

bool validatePath(Path* tmpPath) {
    if (tmpPath->data == NULL || tmpPath->otherAttributes == NULL) {
        return false;
    }

    void* svcAccElement;
    ListIterator accIter = createIterator(tmpPath->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;

        if (validateAttr(tmpAttribute) == false) {
            return false;
        }
    }

    return true;
}

bool validateGroup(Group* tmpGroup) {
    if (tmpGroup->otherAttributes == NULL || tmpGroup->rectangles == NULL || tmpGroup->circles == NULL || tmpGroup->paths == NULL || tmpGroup->groups == NULL) {
        return false;
    }

    void* svcAccElement;
    ListIterator accIter = createIterator(tmpGroup->otherAttributes);
    while ((svcAccElement = nextElement(&accIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)svcAccElement;

        if (validateAttr(tmpAttribute) == false) {
            return false;
        }
    }

    void* rectangleElement;
    ListIterator iter = createIterator(tmpGroup->rectangles);
    while ((rectangleElement = nextElement(&iter)) != NULL) {
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;

        if (validateRect(tmpRectangle) == false) {
            return false;
        }
    }

    void* circleElement;
    ListIterator circleIter = createIterator(tmpGroup->circles);
    while ((circleElement = nextElement(&circleIter)) != NULL) {
        Circle* tmpCircle = (Circle*)circleElement;

        if (validateCircle(tmpCircle) == false) {
            return false;
        }
    }

    void* pathElement;
    ListIterator pathIter = createIterator(tmpGroup->paths);
    while ((pathElement = nextElement(&pathIter)) != NULL) {
        Path* tmpPath = (Path*)pathElement;

        if (validatePath(tmpPath) == false) {
            return false;
        }
    }

    void* groupElement;
    ListIterator groupIter = createIterator(tmpGroup->groups);
    while ((groupElement = nextElement(&groupIter)) != NULL) {
        Group* tmpGroup = (Group*)groupElement;

        if (validateGroup(tmpGroup) == false) {
            return false;
        }
    }

    return true;
}

bool isValidUnit(char units[50]) {
    const char* validUnits[10] = {"rem", "%", "in", "mm", "pc", "pt", "ex", "em", "cm", "px"};
    for (int i = 0; i < 10; i++) {
        if (strcmp(units, validUnits[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool validateXMLTREE(const char* xmlFile, const char* schemaFile) {
    // A function that validates a libxml tree

    xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    const char* XMLFileName = xmlFile;
    const char* XSDFileName = schemaFile;

    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(XSDFileName);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);
    // xmlSchemaDump(stdout, schema); //To print schema dump

    doc = xmlReadFile(XMLFileName, NULL, 0);

    if (doc == NULL) {
        return false;
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    }

    else {
        xmlSchemaValidCtxtPtr ctxt;
        int ret;

        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
        ret = xmlSchemaValidateDoc(ctxt, doc);
        if (ret == 0) {
            //printf("%s validates\n", XMLFileName);
        }

        else if (ret > 0) {
            //printf("%s fails to validate\n", XMLFileName);
            return false;
        }

        else {
            //printf("%s validation generated an internal error\n", XMLFileName);
            return false;
        }

        xmlSchemaFreeValidCtxt(ctxt);
        xmlFreeDoc(doc);
    }

    // free the resource
    if (schema != NULL) {
        xmlSchemaFree(schema);
    }

    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return true;
}

bool covertSVGTOXMLTree(const SVG* img, const char* fileName) {
    //     A function that converts an SVG into an xmlDoc struct, i.e. a libxml tree. This tree can be then be easily saved
    // to disk or validated against an XSD file using libxml functionality.

    xmlDocPtr doc = NULL; /* document pointer */
    xmlNodePtr root_node = NULL;
    xmlNodePtr node = NULL;
    // xmlNodePtr node1 = NULL; /* node pointers */

    xmlNsPtr xmlNSPtr = NULL;
    // char buff[1000000];
    // char buff2[1000000];

    char* buff = malloc(sizeof(char) * 100000000);
    char* buff2 = malloc(sizeof(char) * 1000000);

    void* elem;

    ListIterator iter;
    ListIterator AttributeIter;

    LIBXML_TEST_VERSION;

    // create doc, rootnode
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "svg");
    xmlDocSetRootElement(doc, root_node);

    //*****************************************SVG Namespace, Description, Title ***************************

    unsigned char* pointer = malloc(1000000);

    snprintf((char*)pointer, strlen(img->namespace) + 1000, "%s", img->namespace);

    const unsigned char* buffPointer = pointer;

    xmlNSPtr = xmlNewNs(root_node, buffPointer, NULL);
    xmlSetNs(root_node, xmlNSPtr);

    if (strcmp(img->title, "") != 0) {
        xmlNewChild(root_node, NULL, BAD_CAST "title", BAD_CAST img->title);
    }

    if (strcmp(img->description, "") != 0) {
        xmlNewChild(root_node, NULL, BAD_CAST "desc", BAD_CAST img->description);
    }

    AttributeIter = createIterator(img->otherAttributes);
    while ((elem = nextElement(&AttributeIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)elem;
        strcpy(buff, "");
        strcpy(buff2, "");

        sprintf(buff, "%s", tmpAttribute->name);
        sprintf(buff2, "%s", tmpAttribute->value);
        // strcpy(buff, "dsaa");
        xmlNewProp(root_node, BAD_CAST buff, BAD_CAST buff2);
    }

    //*****************************************Rectangles***************************
    void* rectangleElement;
    iter = createIterator(img->rectangles);
    while ((rectangleElement = nextElement(&iter)) != NULL) {
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;

        sprintf(buff, "%s", "rect");
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%f%s", tmpRectangle->x, tmpRectangle->units);
        xmlNewProp(node, BAD_CAST "x", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->y, tmpRectangle->units);
        xmlNewProp(node, BAD_CAST "y", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->width, tmpRectangle->units);
        xmlNewProp(node, BAD_CAST "width", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->height, tmpRectangle->units);
        xmlNewProp(node, BAD_CAST "height", BAD_CAST buff);

        AttributeIter = createIterator(tmpRectangle->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    //*****************************************Circles***************************

    void* circleElement;
    iter = createIterator(img->circles);
    while ((circleElement = nextElement(&iter)) != NULL) {
        Circle* tmpCircle = (Circle*)circleElement;

        sprintf(buff, "%s", "circle");
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%f%s", tmpCircle->cx, tmpCircle->units);
        xmlNewProp(node, BAD_CAST "cx", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpCircle->cy, tmpCircle->units);
        xmlNewProp(node, BAD_CAST "cy", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpCircle->r, tmpCircle->units);
        xmlNewProp(node, BAD_CAST "r", BAD_CAST buff);

        AttributeIter = createIterator(tmpCircle->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    //*****************************************Paths***************************
    void* pathElement;
    iter = createIterator(img->paths);
    while ((pathElement = nextElement(&iter)) != NULL) {
        Path* tmpPath = (Path*)pathElement;

        sprintf(buff, "%s", "path");
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%s", tmpPath->data);
        xmlNewProp(node, BAD_CAST "d", BAD_CAST buff);

        AttributeIter = createIterator(tmpPath->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    //*****************************************Groups***************************

    void* groupElement;
    iter = createIterator(img->groups);
    while ((groupElement = nextElement(&iter)) != NULL) {
        getGroupForTree(root_node, groupElement, buff, buff2);
    }

    ////*****************************************save file and exit***************************

    xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();

    free(buff);
    free(buff2);
    free(pointer);
    return true;
}

void getGroupForTree(xmlNodePtr parentNode, void* data, char buff[1000000], char buff2[1000000]) {
    xmlNodePtr node = NULL;
    xmlNodePtr node1 = NULL; /* node pointers */

    Group* tmpGroup = (Group*)data;

    void* elem;

    sprintf(buff, "%s", "g");
    node = xmlNewChild(parentNode, NULL, BAD_CAST buff, NULL);

    ListIterator iter;
    ListIterator AttributeIter;

    AttributeIter = createIterator(tmpGroup->otherAttributes);
    while ((elem = nextElement(&AttributeIter)) != NULL) {
        Attribute* tmpAttribute = (Attribute*)elem;
        sprintf(buff, "%s", tmpAttribute->name);
        sprintf(buff2, "%s", tmpAttribute->value);
        xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
    }

    iter = createIterator(tmpGroup->rectangles);

    void* rectangleElement;
    while ((rectangleElement = nextElement(&iter)) != NULL) {
        Rectangle* tmpRectangle = (Rectangle*)rectangleElement;

        sprintf(buff, "%s", "rect");
        node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
        // node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%f%s", tmpRectangle->x, tmpRectangle->units);
        xmlNewProp(node1, BAD_CAST "x", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->y, tmpRectangle->units);
        xmlNewProp(node1, BAD_CAST "y", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->width, tmpRectangle->units);
        xmlNewProp(node1, BAD_CAST "width", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpRectangle->height, tmpRectangle->units);
        xmlNewProp(node1, BAD_CAST "height", BAD_CAST buff);

        AttributeIter = createIterator(tmpRectangle->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node1, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    void* circleElement;
    iter = createIterator(tmpGroup->circles);
    while ((circleElement = nextElement(&iter)) != NULL) {
        Circle* tmpCircle = (Circle*)circleElement;

        sprintf(buff, "%s", "circle");
        node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
        // node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%f%s", tmpCircle->cx, tmpCircle->units);
        xmlNewProp(node1, BAD_CAST "cx", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpCircle->cy, tmpCircle->units);
        xmlNewProp(node1, BAD_CAST "cy", BAD_CAST buff);

        sprintf(buff, "%f%s", tmpCircle->r, tmpCircle->units);
        xmlNewProp(node1, BAD_CAST "r", BAD_CAST buff);

        AttributeIter = createIterator(tmpCircle->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node1, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    void* pathElement;
    iter = createIterator(tmpGroup->paths);
    while ((pathElement = nextElement(&iter)) != NULL) {
        Path* tmpPath = (Path*)pathElement;

        sprintf(buff, "%s", "path");
        node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);

        sprintf(buff, "%s", tmpPath->data);
        xmlNewProp(node1, BAD_CAST "d", BAD_CAST buff);

        AttributeIter = createIterator(tmpPath->otherAttributes);
        while ((elem = nextElement(&AttributeIter)) != NULL) {
            Attribute* tmpAttribute = (Attribute*)elem;
            sprintf(buff, "%s", tmpAttribute->name);
            sprintf(buff2, "%s", tmpAttribute->value);
            xmlNewProp(node1, BAD_CAST buff, BAD_CAST buff2);
        }
    }

    void* groupElement;
    iter = createIterator(tmpGroup->groups);
    while ((groupElement = nextElement(&iter)) != NULL) {
        getGroupForTree(node, groupElement, buff, buff2);
    }
}
