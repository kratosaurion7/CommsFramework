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

    void LoadFile(const char* filePath);

	XmlNode* GetNode(std::string nodeName);

	PointerList<XmlNode*>* GetNodes(std::string nodeName);

private:
	xml_node<>* FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate);

	void FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, PointerList<xml_node<>*> &aggregate);

    FileContents* xmlFile;

    xml_document<>* rootDoc;
};

class XmlNode
{
public:
    XmlNode();
    ~XmlNode();

	std::string NodeName;

	PointerList<XmlNodeAttribute*>* NodeAttributes;

	XmlNodeAttribute* GetAttribute(std::string attributeName);
};

class XmlNodeAttribute
{
public:
	char* AttributeName;

	int valueSize; // TODO : Check if removing this member
	char* AttributeValue; // MUST BE NULL TERMINATED
};