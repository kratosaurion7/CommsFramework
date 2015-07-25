#pragma once

//#define RAPIDXML_NO_EXCEPTIONS // Test

#include "rapidxml.hpp"

#include "BaseList.h"

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

    void LoadFile(char* filePath);

	XmlNode* GetNode(std::string nodeName);

	BaseList<XmlNode*>* GetNodes(std::string nodeName);

private:

    xml_node<>* FindNode(xml_node<>* node, bool(predicate)(rapidxml::xml_node<>* node));

	xml_node<>* FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate);

	void FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*> &aggregate);

    xml_document<>* rootDoc;
};

class XmlNode
{
public:
	char* NodeName;

	BaseList<XmlNodeAttribute*>* NodeAttributes;


	XmlNode();
	~XmlNode();
};

class XmlNodeAttribute
{
public:
	char* AttributeName;

	int valueSize;
	char* AttributeValue;
};