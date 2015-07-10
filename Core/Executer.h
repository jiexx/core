#ifndef __EXECUTER_H__
#define __EXECUTER_H__

#include "StableHeader.h"

class Executer
{
public:
	Executer(void);
	~Executer(void);
	void Execute(Node* root);
	void run(Node* node);
};


#endif
