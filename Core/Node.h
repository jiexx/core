#ifndef __NODE_H__
#define __NODE_H__

#pragma once
class Node
{
public:
	Node(void);
	~Node(void);
	Node* left();
	Node* right();
	virtual void addLeft(Node* n);
	virtual void addMostRight(Node* n); // 1->2->1->2->1, if 2, inserted is 1->2->2, insert (1->2->1) into 1->2 right; if 1, inserted is 1->1->2, insert (1->2->1) into 1->1 right
};

#endif

