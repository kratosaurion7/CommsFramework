#include "XmlReader.h"

#include "FileReader.h"

using namespace rapidxml;

XmlReader::XmlReader()
{
    rootDoc = new xml_document<>();
}

XmlReader::~XmlReader()
{
    delete(rootDoc);
    delete(rootNode);
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

    PointerList<xml_node<>*> listOfStuff;
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

void XmlNode::FindNodeList(xml_node<>* node, std::function<bool(rapidxml::xml_node<>*)> predicate, PointerList<xml_node<>*> &aggregate, bool searchInChildOnly)
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