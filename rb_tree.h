#pragma once

#ifndef NULL
#define NULL 0
#endif
class rb_tree
{
protected:
	typedef enum
	{
		RED,
		BLACK,
	}Color;

	struct node
	{
		node( int k, Color c = RED, node* l=NULL, node* r=NULL, node* p=NULL )
			:parent(p), left(l), right(r), color( c ), key( k )
		{
		}

		node* parent;
		node* left;
		node* right;
		Color color;
		int   key;
	};

public:
	rb_tree(void);
	virtual ~rb_tree(void);

	bool insert( int value );
	bool remove( int value );

protected:
	void insert_fixup( node* c );
	void right_rotate( node* c );
	void left_rotate( node* c );

	void delete_node( node* del );
	rb_tree::node* successor( node* n );
	void delete_fixup( node* child );
private:
	node* root;
	node* nil;
};
