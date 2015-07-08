#include "StdAfx.h"
#include "Builder.h"
#include "Operator.h"
#include "Brace.h"
#include "Operand.h"


#include <string>
#include <stack>
using namespace std;
#pragma once

enum RESULT { 
	SUCCESS						= 0x00000000,
	ERROR						= 0xf0000000,
	E_BUILD_OPERAND_JOIN		= (ERROR+1),
	E_BUILD_OPERATOR_FISRT		= (ERROR+2),
	E_BUILD_BRACE_ABSENT		= (ERROR+3),
	E_BUILD_BRACE_OPERAND_JOIN	= (ERROR+4),
};


