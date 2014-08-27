#include "UIListCtrlCommon.h"

double CalculateDelay(double state)
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
	childs.clear();
}

const NodeData& Node::getData() const
{
	return nodeData;
}

size_t Node::getChildCount() const
{
	return childs.getLength();
}

const Node* Node::getChild(size_t index) const
{
	return childs[index].get();
}

const Node* Node::getParent() const
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
	childs.add(shared_ptr<Node>(child));
}

void Node::removeChild(Node* child)
{
	for (auto& it = childs.begin(); it != childs.end(); ++it)
	{
		if ((*it).get() == child)
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

const Node* Node::getLastChild() const
{
	return childs.getLength() == 0 ? this : childs[childs.getLength() - 1].get();
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}