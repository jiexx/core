#include "StdAfx.h"
#include "Executer.h"


Executer::Executer(void)
{
}


Executer::~Executer(void)
{
}

void Executer::run(Node* node)
{
	if( dynamic_cast<Operator*>(node->left()) ||  dynamic_cast<Operator*>(node->right()) ) {
		run( node->left() );
		run( node->right() );
	}
	Operator* op = dynamic_cast<Operator*>(node);
	if( op ) {
		op->Operate(node->left(), node->right());
	}
}

void Executer::Execute(Node* root)
{
	if( root ) {
		Node* node = root->find(Config::name());
		if( node ) {
			run( node );
		}
	}
}