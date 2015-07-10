#ifndef __NODE_H__
#define __NODE_H__

#include "StableHeader.h"

class Node
{
public:
	Node(void);
	~Node(void);
	Node* left();
	Node* right();
	Node* farRight();
	/*
	 *       1      +     3      ->            1                        1         +      1/0          ->  1/0
	 *      / \                               / \                      / \                               / \
	 *         2                                 2                        2                             1   
	 *        / \                               / \                      / \                           / \     
	 *           1                                 3                        1                             2
	 *          / \                               /                        / \                           / \
	 *             2                             1                            2                             1
	 *            / \                           / \                          / \                           / \ 
	 *                                             2                                                          2
	 *                                            / \                                                        / \
	 *1->2->1->2->1, if 3, inserted is 1->2->3, insert (1->2->1) into 1->2->3 left; if 1, inserted is 1->1->2, insert (1->2->1) into 1 left
	 */
	Node* findMostRight(const Operator* op);
	virtual const char* name();
	virtual const char* serialize();
	virtual void unserialize(const char* buf);

	Node* find( const char* name);
	void addLeft(Node* n);
	void addRight(Node* n); 
};

#endif

