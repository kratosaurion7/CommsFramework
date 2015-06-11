#pragma once

//#define RAPIDXML_NO_EXCEPTIONS // Test

#include "rapidxml.hpp"

struct XmlNode
{
    char    *name;
    char    *value;
    int      size;
};

struct XmlAttribute
{

};

class XmlSearchSyntax;

class XmlReader
{
public:
    XmlReader();
    ~XmlReader();

    void LoadFile(char* filePath);

//protected:
    XmlNode* ReadNode(char* pathSyntax);
    XmlNode** ReadMultipleNodes(char* pathSyntax);
    XmlNode** ReadNodes(char* pathSyntax, int& nodesAmount); // Alternative to the above functions

    XmlAttribute* ReadAttribute(char* pathSyntax, char* attributeName);
    XmlAttribute* ReadAttribute(char* pathSyntax, int attributeIndex);
    XmlAttribute** ReadAttributes(char* pathSyntax, int& nodesAmount); // Alternative for the above functions

private:
    rapidxml::xml_node<>* FindNode(char* pathSyntax);
    rapidxml::xml_node<>* FindNode(char* pathSyntax, rapidxml::xml_node<>* startingNode);

    rapidxml::xml_node<>* Traverse(rapidxml::xml_node<>* node, bool(predicate)(rapidxml::xml_node<>*));
    rapidxml::xml_node<>* Traverse(rapidxml::xml_node<>* node, XmlSearchSyntax *searchNodes, bool(predicate)(rapidxml::xml_node<>*));

    rapidxml::xml_document<>* rootDoc;
};

class XmlSearchSyntax
{
    struct XmlSearchNode{
        char* nodeName;

        XmlSearchNode* nextNode;
    };

public:
    XmlSearchSyntax();
    XmlSearchSyntax(char** searchNodes);
    ~XmlSearchSyntax();

    char* GetNextNode();

    char* ReadCurrentNode();

    bool HasNextNode();

    void AddSearchNode(XmlSearchNode* newNode);

    int GetSyntaxTokensLength();

private:
    XmlSearchNode* firstNode;

    XmlSearchNode* currentNode;
};