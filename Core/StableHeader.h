#include "StdAfx.h"
#include "Builder.h"
#include "Operator.h"
#include "Brace.h"
#include "Operand.h"

enum RESULT { 
	SUCCESS					= 0x00000000,
	ERROR					= 0xf0000000,
	E_VIOLATE_BUILD_RULE	= (ERROR+1),
};


