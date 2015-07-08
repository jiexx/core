#ifndef __BRACE_H__
#define __BRACE_H__


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