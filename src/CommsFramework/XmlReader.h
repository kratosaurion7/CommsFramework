#pragma once

class XmlNode;
class XmlNodeAttribute;
class FileContents;

#include <string>
#include <functional>

#include "rapidxml.hpp"

#include "BaseList.h"
#include "PointerList.h"

using namespace rapidxml;

class XmlReader
{
public:
    XmlReader();
    ~XmlReader();

    void LoadFile(std::string filePath);

	bool IsValid();

    XmlNode* GetNode(std::string nodeName);
    PointerList<XmlNode*>* GetNodes(std::string nodeName);

    XmlNode* FindNode(std::string nodeName, bool searchInChildsOnly = false);
    PointerList<XmlNode*>* FindNodes(std::string nodeName, bool searchInChildsOnly = false);

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

	PointerList<XmlNode*>* GetChildNodes(bool recursive = false);

    // Looks only in immediate child nodes, use chained calls
    XmlNode* GetNode(std::string nodeName);
    PointerList<XmlNode*>* GetNodes(std::string nodeName);

    // Find the node in all the tree of children, if searchInChildOnly is true it will loop out of the current tree of elements and continue looking
    // for the node in the rest of the document.
    XmlNode* FindNode(std::string nodeName, bool searchInChildOnly = false);
    PointerList<XmlNode*>* FindNodes(std::string nodeName, bool searchInChildOnly = false);

    XmlNodeAttribute GetAttribute(std::string attributeName);

private:
    xml_node<>* data_node;

	PointerList<XmlNode*>* CreatedNodesList;

    xml_node<>* FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, bool searchInChildOnly);

    void FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*> &aggregate, bool searchInChildOnly);

    void NodesSearch(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*>* aggregate, bool recursive);
};

class XmlNodeAttribute
{
public:
    char* AttributeName;

    int valueSize; // TODO : Check if removing this member
    char* AttributeValue; // MUST BE NULL TERMINATED

    XmlNodeAttribute();
    ~XmlNodeAttribute();
};