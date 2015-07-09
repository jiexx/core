#include "Builder.h"


Builder::Builder(void)
{
}


Builder::~Builder(void)
{
}

RESULT Builder::build(const char* context, const char* ops, const char* braces, const char* blanks )
{
	if( table_ops.load(ops) && table_braces.load(braces) && table_blanks.load(blanks) ) {
		NodeManager* mgr = NodeManager::getSingleton();
		if( mgr->getHeader() ) {
			return read( mgr->getHeader() );
		}
	}
	return E_BUILD_CONFIG;
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

int Builder::isOp( const char* p )
{
	return table_ops.has(p);
}

int Builder::isBlank(const char* p)
{
	return table_blanks.has(p);
}

int Builder::isBrace(const char* p)
{
	return table_braces.has(p);
}

void Builder::parse( const char* content )
{
	NodeManager* mgr = NodeManager::getSingleton();
	const char* last = content;
	int width;
	while( *content ) {
		if( (width = isBlank(content)) > 0 ) {
			content += width;
		}else if( (width = isOp( content )) > 0 ) {
			mgr->createOperator(content, width);
			mgr->createOperand(content, content-last);
			last = content;
			content += width;
		}else if( (width = isBrace( content )) > 0 ) {
			mgr->createBrace(content, width);
			last = content;
			content += width;
		}
		content ++;
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
	printf(root->name());
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

void Builder::serialize(char* file)
{

}
void Builder::unserialize(const char* file)
{
}

void Builder::brand(Node* node, char** file)
{
	int len = 0;
	if( node ) {
		const char* buf = node->serialize();
		len = strlen( buf );
		memcpy( *file, buf, len );
	}
	memcpy( *file, Config::delimiter().c_stc(), Config::delimiter().length());
	*file += len + Config::delimiter().length();
}
 
void Builder::pack(Node* root, char* file)
{
	brand( root, &file );

	if( root->left() ) {
		pack( root->left(), file );
	}
	brand( root->left(), &file );

	if( root->right() ) {
		pack( root->right(), file );
	}
	brand( root->right(), &file );
}
void Builder::unpack(Node* root, const char* file)
{
	NodeManager* mgr = NodeManager::getSingleton();
	vector<Node*> nodes;
	const char* last = file;
	int width;
	while( file ) {
		if( (width = Config::hasDelimiter( file )) > 0 ) {
			nodes.push_back( mgr->unserialize( file, file - last ) );
			last = file;
			file += width;
		}
		file ++;
	}
	Node* node;
	for( int i = 0 ; i < nodes.size() ; i ++ ) {
		node = nodes.at(i);
		if( node ) {
			node->addLeft( nodes.at(2*i) );
			node->addRight( nodes.at(2*i+1) );
		}
	}
	root = nodes.at(0);
}