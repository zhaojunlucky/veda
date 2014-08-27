#pragma once
#include <UIlib.h>
using namespace DuiLib;

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
	const NodeData& getData() const;
	size_t getChildCount() const;
	const Node* getChild(size_t index) const;
	const Node* getParent() const;
	bool isFolder() const;
	bool hasChild() const;
};