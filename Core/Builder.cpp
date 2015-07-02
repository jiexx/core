#include "Builder.h"


Builder::Builder(void)
{
}


Builder::~Builder(void)
{
}

RESULT Builder::parse( Node* c )
{
	if( dynamic_cast<Operand*>(c) ) {
		if( root != NULL ) {
			if( dynamic_cast<Operator*>(root) )
				root->addMostRight( c );
			else
				return E_VIOLATE_BUILD_RULE;
		}else {
			root = c;
		}
	}else if( dynamic_cast<Operator*>(c) ) {
		if( root != NULL ) {
			if( dynamic_cast<Operand*>(root) ) {
				c->addLeft( root );
				root = c;
			}else if( dynamic_cast<Operator*>(root) ) {
				if( *static_cast<Operator*>(c) > *static_cast<Operator*>(root) ) { //high priority of op, get down in tree
					c->addMostRight( root->right() );
				}else {
					c->addLeft( root );
					root = c;
				}
			}

		}

	}else if( dynamic_cast<LeftBrace*>(c) ) {

	}else if( dynamic_cast<RightBrace*>(c) ) {

	}

}