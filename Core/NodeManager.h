#ifndef __NODEMANAGER_H__
#define __NODEMANAGER_H__

#include "StableHeader.h"


class NodeManager
{
public:
	NodeManager(void);
	~NodeManager(void);
	static NodeManager* getSingleton();
	Node* unserialize(const char* context, int len);
	Operator* createOperator(const char* name, int len);
	Operanad* createOperand(const char* name, int len);
	Brace* createBrace(const char* name, int len);
	Node* getHeader();
};

#endif

