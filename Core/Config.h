#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "StableHeader.h"

class Config
{
public:
	Config(void);
	~Config(void);
	static const string delimiter();
	static int hasDelimiter(const char* str);
	static const string name();
};

#endif

