#pragma once

//#define RAPIDXML_NO_EXCEPTIONS // Test

#include "rapidxml.hpp"

#include "BaseList.h"

#include "PointerList.h"

#include "FileReader.h"

#include <string>

#include <functional>

using namespace rapidxml;

class XmlNode;
class XmlNodeAttribute;


class XmlReader
{
public:
    XmlReader();
    ~XmlReader();

    void LoadFile(std::string filePath);

    XmlNode* GetNode(std::string nodeName);

    PointerList<XmlNode*>* GetNodes(std::string nodeName);

private:
    FileContents* xmlFile;

    xml_document<>* rootDoc;

    XmlNode* rootNode;
};

class XmlNode
{
public:
    XmlNode(xml_node<>* xmlData);
    ~XmlNode();

    std::string NodeName();

    std::string Contents();

    XmlNode* GetNode(std::string nodeName, bool searchInChildOnly = false);

    PointerList<XmlNode*>* GetNodes(std::string nodeName, bool searchInChildOnly = false);

    XmlNodeAttribute GetAttribute(std::string attributeName);

private:
    xml_node<>* data_node;

    xml_node<>* FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, bool searchInChildOnly);

    void FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, PointerList<xml_node<>*> &aggregate, bool searchInChildOnly);
};

class XmlNodeAttribute
{
public:
    char* AttributeName;

    int valueSize; // TODO : Check if removing this member
    char* AttributeValue; // MUST BE NULL TERMINATED
};