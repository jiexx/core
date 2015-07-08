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
						Node* node = root->findMostRight( c );
						Node* right = node->right();
						node->addRight( c );
						c->addLeft( right );
					}else {
						c->addLeft( root );
						root = c;
					}
				}
			}else if( !node_pop.empty() ){
				c->addLeft( node_pop.top() );
				root = c;
				node_pop.pop();
			}else {
				return E_BUILD_OPERATOR_FISRT;
			}
		}else if( dynamic_cast<LeftBrace*>(c) ) {
			node_stack.push( root );
			root = 0;
			continue;
		}else if( dynamic_cast<RightBrace*>(c) ) {
			if( root ) {
				if( !node_stack.empty() ) {
					Node* top = node_stack.top();
					if( top ) {
						Node* node = top->farRight();
						if( dynamic_cast<Operator*>(node) && !node->left() ) {
							node->addLeft( root );
							root = node;
						}else {
							return E_BUILD_BRACE_OPERAND_JOIN;
						}
					}else {
						node_pop.push(root);
						root = 0;
					}
				}else {
					return E_BUILD_BRACE_ABSENT;
				}
			}
			node_stack.pop();
		}
	}
}

bool Builder::match( const char* p )
{
	int i;
	for( i = 0 ; i < table_op.count() ; i ++ ) {
		if( strcmp(p, table_op.get(i)) )
			break;
	}
	if( i < table_op.count() )
		return true;
	return false;
}

RESULT Builder::parse( const char* content )
{
	const char* p;
	while( *content ) {
		if( match( content ) )
		
	}
}

void Builder::debugPrint()
{
	int level = 0;

	print( root, &level );
}

void Builder::print( Node* root, int* level )
{
	if( root->left() || root->right() )
		*level ++;
	if( root->left() ) {
		print( root->left(), level );
	}
	if( root->right() ) {
		print( root->right(), level );
	}
	for( int i = 0 ; i < 2*(*level) ; i ++ )
		printf(" ");
	printf(root->name().c_str());
	printf("\n");
	if( root->left() ) {
		for( int i = 0 ; i < (*level) ; i ++ )
			printf(" ");
		printf("/");
	}
	if( root->left() ) {
		for( int i = 0 ; i < 3*(*level) ; i ++ )
			printf(" ");
		printf("\\");
	}
}