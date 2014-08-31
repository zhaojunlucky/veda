#include "UIListCtrlCommon.h"

double calculateDelay(double state)
{
	return pow(state, 2);
}

Node::Node()
	:parent(nullptr)
{

}

Node::Node(NodeData t)
	: parent(nullptr), nodeData(t)
{

}

Node::Node(NodeData t, Node* parent)
	: parent(parent), nodeData(t)
{

}

Node::~Node()
{
	for (int i = 0; i < childs.getLength(); ++i)
	{
		delete childs[i];
	}
	childs.clear();
}

NodeData& Node::getData()
{
	return nodeData;
}

size_t Node::getChildCount() const
{
	return childs.getLength();
}

Node* Node::getChild(size_t index)
{
	return childs[index];
}

Node* Node::getParent()
{
	return parent;
}

bool Node::isFolder() const
{
	return nodeData.folder;
}

bool Node::hasChild() const
{
	return childs.getLength() > 0;
}

void Node::addChild(Node* child)
{
	child->setParent(this);
	childs.add(child);
}

void Node::removeChild(Node* child)
{
	for (auto& it = childs.begin(); it != childs.end(); ++it)
	{
		if ((*it) == child)
		{
			childs.removeAt(it);
			break;
		}
	}
}

void Node::clearChild()
{
	childs.clear();
}

Node* Node::getLastChild()
{
	return childs.getLength() == 0 ? this : childs[childs.getLength() - 1];
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}