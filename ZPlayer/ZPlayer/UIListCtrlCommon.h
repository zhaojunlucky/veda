#pragma once
#include <UIlib.h>
using namespace DuiLib;
#include <Vector.h>
using namespace veda;

struct NodeData
{
	int level;
	bool folder;
	bool childVisible;
	bool hasChild;
	CDuiString text;
	CDuiString value;
	CListContainerElementUI* listElement;
};

double calculateDelay(double state);

class Node
{
public:
	Node();
	explicit Node(NodeData t);
	Node(NodeData t, Node* parent);
	~Node();
	NodeData& getData();
	size_t getChildCount() const;
	Node* getChild(size_t index);
	Node* getParent();
	bool isFolder() const;
	bool hasChild() const;
	void addChild(Node* child);
	void removeChild(Node* child);
	void clearChild();
	Node* getLastChild();
private:
	void setParent(Node* parent);
private:
	Node* parent;
	NodeData nodeData;
	Vector<Node*> childs;
};