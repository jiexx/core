#ifndef __BUILDER_H__
#define __BUILDER_H__

#pragma once
#include "StableHeader.h"

class Builder
{
public:
	Builder(void);
	~Builder(void);
	Node* split(const char* text);
	RESULT read( Node* c );
protected:
	Node* root;
	stack<Node*> node_stack;
};

#endif
