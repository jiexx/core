#ifndef __BRACE_H__
#define __BRACE_H__

#pragma once
class Brace : public Node
{
public:
	Brace(void);
	~Brace(void);
};
class LeftBrace : public Brace
{
public:
	LeftBrace(void);
	~LeftBrace(void);
};
class RightBrace : public Brace
{
public:
	RightBrace(void);
	~RightBrace(void);
};

#endif