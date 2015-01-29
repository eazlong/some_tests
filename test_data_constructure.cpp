#include "rb_tree.h"
#include "mininum_heap.h"
#include <iostream>
using namespace std;

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

void test_minimum_heap()
{
	mininum_heap<int> tree( 100 );
	tree.push( 30 );
	tree.push( 20 );
	tree.push( 10 );
	tree.push( 5 );
	tree.push( 7 );
	tree.push( 31 );
	tree.push( 32 );
	tree.push( 1 );
	tree.push( 100 );
	tree.push( 2 );
	tree.push( 200 );
	tree.push( 3 );
	tree.push( 300 );
	
	int i;
	while ( tree.pop( i ) )
	{
		cout << i << "-";
	}
	cout << endl;
}
