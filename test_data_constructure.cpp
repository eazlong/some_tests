#include "rb_tree.h"

void test_rb_tree()
{
	rb_tree tree;
	tree.insert( 30 );
	tree.insert( 20 );
	tree.insert( 10 );
	tree.insert( 5 );
	tree.insert( 7 );
	tree.insert( 31 );
	tree.insert( 32 );

	tree.remove( 20 );
	tree.remove( 7 );
	tree.remove( 30 );
	tree.remove( 31 );
}