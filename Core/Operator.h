#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#pragma once
#include "Node.h"

class Operator : public Node
{
public:
	Operator(void);
	~Operator(void);
	bool operator < (const Operator& op) const;
	bool operator > (const Operator& op) const;
};

#endif

