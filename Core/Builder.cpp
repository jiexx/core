#include "Builder.h"


Builder::Builder(void)
{
}


Builder::~Builder(void)
{
}

RESULT Builder::read( Node* c )
{
	while( c++ ) {
		if( dynamic_cast<Operand*>(c) ) {
			if( root ) {
				if( dynamic_cast<Operator*>(root) )
					root->addRight( c );
				else
					return E_BUILD_OPERAND_JOIN;
			}else {
				root = c;
			}
		}else if( dynamic_cast<Operator*>(c) ) {
			if( root ) {
				if( dynamic_cast<Operand*>(root) ) {
					c->addLeft( root );
					root = c;
				}else if( dynamic_cast<Operator*>(root) ) {
					if( *static_cast<Operator*>(c) > *static_cast<Operator*>(root) ) { //high priority of op, get down in tree
						Node* node = c->findMostRight( c );
						node->addRight( root );
					}else {
						c->addLeft( root );
						root = c;
					}
				}
			}else {
				return E_BUILD_OPERATOR_FISRT;
			}
		}else if( dynamic_cast<LeftBrace*>(c) ) {
			node_stack.push( root );
			continue;
		}else if( dynamic_cast<RightBrace*>(c) ) {
			if( root ) {
				if( !node_stack.empty() ) {
					Node* n = node_stack.top();
					if( n ) {
						Node* node = n->findMostRight( root );
					}else {
					}
					node_stack.pop();
				}else {
					return E_BUILD_BRACE_ABSENT;
				}
			}
		}
	}

}