#include "XmlReader.h"

#include "IO/FileReader.h"

using namespace rapidxml;

XmlReader::XmlReader()
{
    rootDoc = new xml_document<>();
	rootNode = NULL;
	xmlFile = NULL;
}

XmlReader::~XmlReader()
{
	if(rootDoc != NULL)
		delete(rootDoc);
	
	if(rootNode != NULL)
		delete(rootNode);

	if(xmlFile != NULL)
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

        rootNode = new XmlNode(rootDoc->first_node());
    }
}

bool XmlReader::IsValid()
{
	return this->xmlFile != NULL;
}

XmlNode * XmlReader::GetNode(std::string nodeName)
{
    return rootNode->GetNode(nodeName);
}

PointerList<XmlNode*>* XmlReader::GetNodes(std::string nodeName)
{
    return rootNode->GetNodes(nodeName);
}

XmlNode* XmlReader::FindNode(std::string nodeName, bool searchInChildsOnly)
{
    return rootNode->FindNode(nodeName, searchInChildsOnly);
}

PointerList<XmlNode*>* XmlReader::FindNodes(std::string nodeName, bool searchInChildsOnly)
{
    return rootNode->FindNodes(nodeName, searchInChildsOnly);
}

XmlNode::XmlNode(xml_node<>* xmlData)
{
    data_node = xmlData;
	CreatedNodesList = new PointerList<XmlNode*>();
}

XmlNode::~XmlNode()
{
    //NodeAttributes->Release(); // TODO : Create a Delete() method.
    //delete(NodeAttributes);

	CreatedNodesList->Release();
	delete(CreatedNodesList);
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

PointerList<XmlNode*>* XmlNode::GetChildNodes(bool recursive)
{
	auto pred = [](rapidxml::xml_node<>*node) -> bool {
		return true;
	};

	PointerList<XmlNode*>* nodeList = new PointerList<XmlNode*>();
    PointerList<xml_node<>*> listOfStuff = PointerList<xml_node<>*>();

	this->NodesSearch(this->data_node->first_node(), pred, &listOfStuff, true);

	auto stuff = listOfStuff.GetContainer();

	auto it = stuff->begin();
	while (it != listOfStuff.GetContainer()->end())
	{
		auto item = *it;

		XmlNode* foundNode = new XmlNode(item);

		CreatedNodesList->Add(foundNode);

		nodeList->Add(foundNode);

		it++;
	}

	return nodeList;
}

XmlNode * XmlNode::GetNode(std::string nodeName)
{
    rapidxml::xml_node<>* firstNode = this->data_node->first_node(nodeName.c_str());

    if (firstNode != NULL)
    {
        XmlNode* foundNode = new XmlNode(firstNode);
        CreatedNodesList->Add(foundNode);

        return foundNode;
    }
    else
    {
        return NULL;
    }
}

PointerList<XmlNode*>* XmlNode::GetNodes(std::string nodeName)
{
    rapidxml::xml_node<>* nextNode = this->data_node->first_node(nodeName.c_str());

    PointerList<XmlNode*>* ret = new PointerList<XmlNode*>();

    while (nextNode != NULL)
    {
        XmlNode* foundNode = new XmlNode(nextNode);
        ret->Add(foundNode);

        nextNode = nextNode->next_sibling(nodeName.c_str());

        CreatedNodesList->Add(foundNode);
    }

    return ret;
}

XmlNodeAttribute XmlNode::GetAttribute(std::string attributeName)
{
    if (data_node != NULL)
    {
        XmlNodeAttribute returnAttr;

        auto attr = data_node->first_attribute(attributeName.c_str());

        if (attr != NULL)
        {
            strcpy(returnAttr.AttributeName, attr->name());
            //returnAttr.AttributeName = attr->name();
            strcpy(returnAttr.AttributeValue, attr->value());
            //returnAttr.AttributeValue = attr->value();
            returnAttr.valueSize = (int)attr->value_size();

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

XmlNode* XmlNode::FindNode(std::string nodeName, bool searchInChildOnly)
{
    auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
        return strcmp(node->name(), nodeName.c_str()) == 0;
    };

    auto ret = FindNode(data_node, pred, searchInChildOnly);

    if (ret != NULL)
    {
        XmlNode* foundNode = new XmlNode(ret);

		CreatedNodesList->Add(foundNode);

        return foundNode;
    }
    else
    {
        return NULL;
    }
}

PointerList<XmlNode*>* XmlNode::FindNodes(std::string nodeName, bool searchInChildOnly)
{
    auto pred = [nodeName](rapidxml::xml_node<>*node) -> bool {
        return strcmp(node->name(), nodeName.c_str()) == 0;
    };

    BaseList<xml_node<>*> listOfStuff;
    PointerList<XmlNode*>* nodeList = new PointerList<XmlNode*>();

    FindNodeList(data_node, pred, listOfStuff, searchInChildOnly);

    auto stuff = listOfStuff.GetContainer();

    auto it = stuff->begin();
    while (it != listOfStuff.GetContainer()->end())
    {
        auto item = *it;

        XmlNode* foundNode = new XmlNode(item);
		
		CreatedNodesList->Add(foundNode);

        nodeList->Add(foundNode);

        it++;
    }

    return nodeList;
}

xml_node<>* XmlNode::FindNode(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, bool searchInChildOnly)
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
        {
            nextNode = node->next_sibling();
        }

        if (searchInChildOnly == false)
        {
            if (nextNode == NULL && node->parent())
            {
                nextNode = node->parent()->next_sibling();
            }

            rapidxml::xml_node<>* nextParent = node;
            while (nextNode == NULL)
            {
                nextParent = nextParent->parent();

                if (nextParent->type() == node_document)
                    return NULL;

                nextNode = nextParent->next_sibling();
            }
        }

        return FindNode(nextNode, predicate, searchInChildOnly);
    }
}

void XmlNode::FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*> &aggregate, bool searchInChildOnly)
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

    if (!searchInChildOnly)
    {
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
    }

    FindNodeList(nextNode, predicate, aggregate, searchInChildOnly);
}

void XmlNode::NodesSearch(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, BaseList<xml_node<>*>* aggregate, bool recursive)
{
    if (node == NULL)
        return;

    // If the node has children, it doesn't contain parameters but probably contains other parameters so don't add it
    bool hasChildren = false;

    if (node->first_node() != NULL && node->first_node()->type() != node_data)
    {
        hasChildren = true;
    }

    if (predicate(node) && !hasChildren)
    {
        aggregate->Add(node);
    }

    if (recursive)
    {
        xml_node<>* child = node->first_node();

        if (child != NULL && child->type() != node_data)
        {
            NodesSearch(child, predicate, aggregate, recursive);
        }
    }

    rapidxml::xml_node<>* nextNode = node->next_sibling();

    if (nextNode == NULL)
        return;

    NodesSearch(nextNode, predicate, aggregate, recursive);
}

XmlNodeAttribute::XmlNodeAttribute()
{
    strcpy(this->AttributeName, "");
    strcpy(this->AttributeValue, "");
}

XmlNodeAttribute::~XmlNodeAttribute()
{
    //delete(this->AttributeName);
    //delete(this->AttributeValue);
}
