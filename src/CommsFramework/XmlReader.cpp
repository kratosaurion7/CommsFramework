#include "XmlReader.h"

#include "rapidxml.hpp"

#include "FileReader.h"

#include "Macros.h"

#include <functional>

using namespace rapidxml;

XmlReader::XmlReader()
{
    rootDoc = new xml_document<>();
};

XmlReader::~XmlReader()
{
    delete(rootDoc);
};

void XmlReader::LoadFile(char* filePath)
{
    FileReader reader;
    reader.OpenFile(filePath, READ);

    FileContents *xmlFile = reader.GetFileContents();

    if (xmlFile != NULL)
    {
        rootDoc->parse<0>((char*)xmlFile->buffer); // TODO : Unsafe conversion from const to non-const
    }
};

// catalog/book/author=[Ralls]
// catalog/book={id=blabla}


XmlNode** XmlReader::ReadMultipleNodes(char* pathSyntax)
{
    return NULL;
};

XmlNode** XmlReader::ReadNodes(char* pathSyntax, int& nodesAmount)
{
    return NULL;
};

XmlAttribute* XmlReader::ReadAttribute(char* pathSyntax, char* attributeName)
{
    return NULL;
};

XmlAttribute* XmlReader::ReadAttribute(char* pathSyntax, int attributeIndex)
{
    return NULL;
};

XmlAttribute** XmlReader::ReadAttributes(char* pathSyntax, int& nodesAmount)
{
    return NULL;
};


// Private Functions
rapidxml::xml_node<>* XmlReader::FindNode(char* pathSyntax) // catalog/book/subitem/other/nextval
{

    return this->FindNode(pathSyntax, rootDoc);
};

rapidxml::xml_node<>* XmlReader::FindNode(char* pathSyntax, rapidxml::xml_node<>* startingNode)
{
    char** tokens; // catalog, book, subitem, other, nextval
    int tokensNb = sizeof(tokens);


    return NULL;
};

XmlNode* XmlReader::ReadNode(char* pathSyntax)
{
    auto f = [](rapidxml::xml_node<>* node) -> bool { return strcmp(node->value(), "abcd") == 0; };

    auto f2 = [](rapidxml::xml_node<>* node) -> bool { return strcmp(node->value(), "Computer") == 0; };

    char *names[50];
    names[0] = "book";
    names[1] = "subitem";
    names[2] = "other";
    names[3] = "nextval";

    XmlSearchSyntax *search = new XmlSearchSyntax(names);

    auto catalog = rootDoc->first_node();

    //auto x = this->Traverse(catalog, names, f);

    //auto y = this->Traverse(catalog, f2);

    auto z = this->Traverse(catalog, search, f);

    return NULL;
};

/*
  This function searches for a node that matches a predicate. This function is non-deterministic and will search
  until a result is found or the end of the document is reached.
*/
rapidxml::xml_node<>* XmlReader::Traverse(rapidxml::xml_node<>* node, bool(predicate)(rapidxml::xml_node<>*))
{
    if (node == NULL)
        return NULL;

    if (predicate(node))
    {
        return node;
    }
    else
    {
        rapidxml::xml_node<>* nextNode = node->first_node();

        if (nextNode == NULL)
            nextNode = node->next_sibling();

        if (nextNode->type() == node_data)
            nextNode = node->next_sibling();


        return Traverse(nextNode, predicate);
    }
};

/*
This function searches for a node that matches a predicate. The function uses an object to search for the xml element.
children node to search for.

This is mostly used when needing to quickly traverse the document in search of a particular value of a known xml element.
*/
rapidxml::xml_node<>* XmlReader::Traverse(rapidxml::xml_node<>* node, XmlSearchSyntax *searchNodes, bool(predicate)(rapidxml::xml_node<>*))
{
    if (node == NULL || searchNodes == NULL)
        return NULL;

    if (searchNodes->ReadCurrentNode() == NULL)
        return NULL;

    if (predicate(node))
    {
        return node;
    }
    else
    {
        rapidxml::xml_node<>* nextNode = node->first_node(searchNodes->ReadCurrentNode());

        if (nextNode == NULL)
        {
            nextNode = node->next_sibling();

            if (nextNode == NULL)
                return NULL;
        }

        if (nextNode->type() == node_data)
            nextNode = node->next_sibling();

        searchNodes->GetNextNode();

        return Traverse(nextNode, searchNodes, predicate);
    }
};


XmlSearchSyntax::XmlSearchSyntax()
{
    firstNode = NULL;
    
    currentNode = NULL;
};

XmlSearchSyntax::XmlSearchSyntax(char** searchNodes)
{
    int strings = sizeof(searchNodes);

    if (strings == 1)
    {
        XmlSearchNode *node = new XmlSearchNode();
        node->nodeName = searchNodes[0];

        firstNode = node;
    }
    else
    {
        XmlSearchNode *nextNode = new XmlSearchNode();
        nextNode->nodeName = searchNodes[0];

        firstNode = nextNode;

        for (int i = 1; i < strings; i++)
        {
            XmlSearchNode *node = new XmlSearchNode();
            node->nodeName = searchNodes[i];
            nextNode->nextNode = node;

            nextNode = node;
        }
    }
    
    currentNode = firstNode;
};

XmlSearchSyntax::~XmlSearchSyntax()
{
    XmlSearchNode *node = this->firstNode;

    while (node != NULL)
    {
        XmlSearchNode *nextNode = node->nextNode;
        
        SAFE_DELETE(node->nodeName);
        SAFE_DELETE(node);
        
        node = nextNode;
    }
};

// Gets the name of the next node and advances the current node pointer.
char* XmlSearchSyntax::GetNextNode()
{
    if (!this->HasNextNode())
        return NULL;

    XmlSearchNode *nextNode = currentNode->nextNode;  

    currentNode = nextNode;

    return nextNode->nodeName;
};

char* XmlSearchSyntax::ReadCurrentNode()
{
    return currentNode != NULL ? currentNode->nodeName : NULL;
}

bool XmlSearchSyntax::HasNextNode()
{
    return currentNode->nextNode != NULL;
};

void XmlSearchSyntax::AddSearchNode(XmlSearchNode* newNode)
{
    XmlSearchNode *lastNode = firstNode;

    while (lastNode->nextNode != NULL)
    {
        lastNode = lastNode->nextNode;
    }

    lastNode->nextNode = newNode;
};

int XmlSearchSyntax::GetSyntaxTokensLength()
{
    XmlSearchNode *lastNode = firstNode;

    int total = 0;

    while (lastNode->nextNode != NULL)
    {
        lastNode = lastNode->nextNode;
        total++;
    }

    return total;
};
