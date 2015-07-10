#ifndef __BUILDER_H__
#define __BUILDER_H__

#include "StableHeader.h"

class Builder
{
public:
	Builder(void);
	~Builder(void);
	Node* split(const char* text);
	RESULT read( Node* c );
	RESULT build(const char* context, const char* ops, const char* braces, const char* blanks );
	void parse( const char* context );
	void debugPrint(void);
	void serialize(char* file);
	void unserialize(const char* file);
protected:
	class Symbols {
	public:
		bool load(const char* str);
		int count();
		int width();
		int has(const char* p );
		const char* get(int index);
	};
	void pack(Node* node, char* file);
	void brand(Node* node, char** file);
	void print(Node* root, int* level);
	int isOp(const char* p);
	int isBlank(const char* p);
	int isBrace(const char* p);
protected:
	Node* root;
	stack<Node*> node_pop;
	stack<Node*> node_stack;
	Symbols table_ops;
	Symbols table_blanks;
	Symbols table_braces;
};

#endif
