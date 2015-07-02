#ifndef __BUILDER_H__
#define __BUILDER_H__

#pragma once
#include "StableHeader.h"

class Builder
{
public:
	Builder(void);
	~Builder(void);
	RESULT parse( Node* c );
protected:
	Node* root;
};

#endif
