#include "XmlReader.h"

#include "rapidxml.hpp"

#include "FileReader.h"

#include "Macros.h"

#include <functional>

class XmlNode;
class XmlNodeAttribute;

using namespace rapidxml;

XmlReader::XmlReader()
{
    rootDoc = new xml_document<>();
}

XmlReader::~XmlReader()
{
    delete(rootDoc);
}

void XmlReader::LoadFile(char* filePath)
{
    FileReader reader;
    reader.OpenFile(filePath);

    FileContents *xmlFile = reader.GetFileContents();

    if (xmlFile != NULL)
    {
        rootDoc->parse<0>(xmlFile->buffer); // TODO : Unsafe conversion from const to non-const
    }
}

XmlNode * XmlReader::GetNode(std::string nodeName)
{
	auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
		return strcmp(node->name(),nodeName.c_str()) == 0;
	};


	auto test = [](rapidxml::xml_node<>*) {
		return true;
	};

	auto ret = FindNode2(rootDoc, pred);

	if (ret != NULL)
	{
		XmlNode* foundNode = new XmlNode();
		foundNode->NodeName = ret->name();
		
		auto attr = ret->first_attribute();
		
		while (attr != NULL)
		{
			XmlNodeAttribute* newAttribute = new XmlNodeAttribute();
			newAttribute->AttributeName = attr->name();
			newAttribute->AttributeValue = attr->value();
			newAttribute->valueSize = attr->value_size();
			
			foundNode->NodeAttributes->Add(newAttribute);

			attr = attr->next_attribute();
		}

		return foundNode;
	}
	else 
	{
		return NULL;
	}
}


BaseList<XmlNode*>* XmlReader::GetNodes(std::string nodeName)
{
	return nullptr;
}

xml_node<>* XmlReader::FindNode(xml_node<>* node, bool(predicate)(rapidxml::xml_node<>*node))
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


		return FindNode(nextNode, predicate);
	}
}

xml_node<>* XmlReader::FindNode2(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate)
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


		return FindNode2(nextNode, predicate);
	}
}

BaseList<xml_node<>*>* XmlReader::FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*> &aggregate)
{
	if (node == NULL)
		return NULL;

	if (predicate(node))
	{
		aggregate.Add(node);
	}

	rapidxml::xml_node<>* nextNode = node->first_node();

	if (nextNode == NULL)
		nextNode = node->next_sibling();

	if (nextNode->type() == node_data)
		nextNode = node->next_sibling();


	return FindNodeList(nextNode, predicate, aggregate);
}

XmlNode::XmlNode()
{
	NodeAttributes = new BaseList<XmlNodeAttribute*>();
}

XmlNode::~XmlNode()
{
	NodeAttributes->Clear(); // TODO : Create a Delete() method.

	delete(NodeAttributes);
}
