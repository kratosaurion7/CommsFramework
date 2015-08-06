#include "XmlReader.h"

#include "rapidxml.hpp"

#include "FileReader.h"

#include "Macros.h"

#include <string>
#include <functional>

//class XmlNode;
//class XmlNodeAttribute;

using namespace rapidxml;

XmlReader::XmlReader()
{
    rootDoc = new xml_document<>();
}

XmlReader::~XmlReader()
{
    delete(rootDoc);

    delete(xmlFile);
}

void XmlReader::LoadFile(std::string filePath)
{
    FileReader reader;
    reader.OpenFile(filePath.c_str());

    xmlFile = reader.GetFileContents(true);

    reader.Close();

    if (xmlFile != NULL)
    {
        rootDoc->parse<0>(xmlFile->buffer); // TODO : Unsafe conversion from const to non-const
    }
}

XmlNode* XmlReader::GetNode(std::string nodeName)
{
	auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
		return strcmp(node->name(),nodeName.c_str()) == 0;
	};

	auto ret = FindNode(rootDoc, pred);

	if (ret != NULL)
	{
		XmlNode* foundNode = new XmlNode(ret);
		

		return foundNode;
	}
	else 
	{
		return NULL;
	}
}


PointerList<XmlNode*>* XmlReader::GetNodes(std::string nodeName)
{
	auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
		return strcmp(node->name(), nodeName.c_str()) == 0;
	};
	
	PointerList<xml_node<>*> listOfStuff;
	PointerList<XmlNode*>* nodeList = new PointerList<XmlNode*>();

	FindNodeList(rootDoc, pred, listOfStuff);

	auto stuff = listOfStuff.GetContainer();

	auto it = stuff->begin();

	while (it != listOfStuff.GetContainer()->end())
	{
		auto item = *it;

		XmlNode* foundNode = new XmlNode(item);

		nodeList->Add(foundNode);

		it++;
	}

	return nodeList;
}

xml_node<>* XmlReader::FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate)
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

		if (nextNode == NULL || nextNode->type() == node_data)
			nextNode = node->next_sibling();

		if (nextNode == NULL && node->parent())
			nextNode = node->parent()->next_sibling();

		rapidxml::xml_node<>* nextParent = node;
		while (nextNode == NULL)
		{
			nextParent = nextParent->parent();
			
			if (nextParent->type() == node_document)
				return NULL;

			nextNode = nextParent->next_sibling();
		}

		return FindNode(nextNode, predicate);
	}
}

void XmlReader::FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, PointerList<xml_node<>*> &aggregate)
{
	if (node == NULL)
		return;

	if (predicate(node))
	{
		aggregate.Add(node);
	}

	rapidxml::xml_node<>* nextNode = node->first_node();

	if (nextNode == NULL || nextNode->type() == node_data)
		nextNode = node->next_sibling();

	if (nextNode == NULL && node->parent())
		nextNode = node->parent()->next_sibling();

	rapidxml::xml_node<>* nextParent = node;
	while (nextNode == NULL)
	{
		nextParent = nextParent->parent();

		if (nextParent->type() == node_document)
			return;
		
		nextNode = nextParent->next_sibling();
	}

	FindNodeList(nextNode, predicate, aggregate);
}

XmlNode::XmlNode(xml_node<>* xmlData)
{
	//NodeAttributes = new PointerList<XmlNodeAttribute*>();

	data_node = xmlData;
}

XmlNode::~XmlNode()
{
	//NodeAttributes->Release(); // TODO : Create a Delete() method.
	//delete(NodeAttributes);
}

std::string XmlNode::NodeName()
{
	if (data_node != NULL)
	{
		return data_node->name();
	}
	else 
	{
		return "";
	}
}

std::string XmlNode::Contents()
{
	if (data_node != NULL)
	{
		return data_node->value();
	}
	else
	{
		return "";
	}
}


XmlNodeAttribute XmlNode::GetAttribute(std::string attributeName)
{
	if (data_node != NULL)
	{
        XmlNodeAttribute returnAttr;

		auto attr = data_node->first_attribute(attributeName.c_str());

		if (attr != NULL)
		{
			returnAttr.AttributeName = attr->name();
			returnAttr.AttributeValue = attr->value();
			returnAttr.valueSize = attr->value_size();

			return returnAttr;
		}
		else 
		{
			return XmlNodeAttribute();
		}
	}
	else 
	{
		return XmlNodeAttribute();
	}
}

XmlNode* XmlNode::GetNode(std::string nodeName)
{
	auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
		return strcmp(node->name(), nodeName.c_str()) == 0;
	};

	auto ret = FindNode(data_node, pred);

	if (ret != NULL)
	{
		XmlNode* foundNode = new XmlNode(ret);

		return foundNode;
	}
	else
	{
		return NULL;
	}
}


PointerList<XmlNode*>* XmlNode::GetNodes(std::string nodeName)
{
	auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
		return strcmp(node->name(), nodeName.c_str()) == 0;
	};

	PointerList<xml_node<>*> listOfStuff;
	PointerList<XmlNode*>* nodeList = new PointerList<XmlNode*>();

	FindNodeList(data_node, pred, listOfStuff);

	auto stuff = listOfStuff.GetContainer();

	auto it = stuff->begin();

	while (it != listOfStuff.GetContainer()->end())
	{
		auto item = *it;

		XmlNode* foundNode = new XmlNode(item);

		nodeList->Add(foundNode);

		it++;
	}

	return nodeList;
}


xml_node<>* XmlNode::FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate)
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

		if (nextNode == NULL || nextNode->type() == node_data)
			nextNode = node->next_sibling();

		if (nextNode == NULL && node->parent())
			nextNode = node->parent()->next_sibling();

		rapidxml::xml_node<>* nextParent = node;
		while (nextNode == NULL)
		{
			nextParent = nextParent->parent();

			if (nextParent->type() == node_document)
				return NULL;

			nextNode = nextParent->next_sibling();
		}

		return FindNode(nextNode, predicate);
	}
}

void XmlNode::FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, PointerList<xml_node<>*> &aggregate)
{
	if (node == NULL)
		return;

	if (predicate(node))
	{
		aggregate.Add(node);
	}

	rapidxml::xml_node<>* nextNode = node->first_node();

	if (nextNode == NULL || nextNode->type() == node_data)
		nextNode = node->next_sibling();

	if (nextNode == NULL && node->parent())
		nextNode = node->parent()->next_sibling();

	rapidxml::xml_node<>* nextParent = node;
	while (nextNode == NULL)
	{
		nextParent = nextParent->parent();

		if (nextParent->type() == node_document)
			return;

		nextNode = nextParent->next_sibling();
	}

	FindNodeList(nextNode, predicate, aggregate);
}

