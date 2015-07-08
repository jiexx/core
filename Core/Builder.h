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
	RESULT parse( const char* context );
	void debugPrint(void);
protected:
	class Ops {
	public:
		int count();
		int width();
		const char* get(int index);
	}
	void print(Node* root, int* level);
	bool match(const char* p);
protected:
	Node* root;
	stack<Node*> node_pop;
	stack<Node*> node_stack;
	Ops table_op;
};

#endif
