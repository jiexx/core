#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "StableHeader.h"

class Operator : public Node
{
public:
	Operator(void);
	~Operator(void);
	void Operate(Operand* left, Operand* right);
	bool operator < (const Operator& op) const;
	bool operator > (const Operator& op) const;
};

#endif

