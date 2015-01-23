#include "rb_tree.h"
#include <iostream>
using namespace std;

rb_tree::rb_tree(void)
:root(NULL),nil(NULL)
{
}

rb_tree::~rb_tree(void)
{
}

bool rb_tree::insert( int value )
{
	if ( root == NULL )
	{
		nil  = new node( 0, BLACK );              //创建空结点以减少对边界结点指针为ＮＵＬＬ的判断
		root = new node( value, BLACK, nil, nil );//根结点 
		return true;
	}

	node* cur = root;
	node* parent = NULL;
	while ( cur != nil )                          //查找适合插入的位置,比当前结点小则查找左结点，大则找右结点
	{
		parent = cur;
		if ( cur->key > value )
		{
			cur = cur->left;
		}
		else if ( cur->key < value )
		{
			cur = cur->right;
		}
		else
		{
			cout << "duplicate value:" << value << endl;
			return false;
		}
	}

	cur = new node( value, RED, nil, nil, parent );
	if ( parent->key > value )
	{
		parent->left = cur;
	}
	else
	{
		parent->right = cur;
	}
	
	insert_fixup( cur );                            //插入的结点可能会导致不满足红黑树的条件，需要调整
	return true;
}

//插入元素之后更新状态
void rb_tree::insert_fixup( node* c )
{
	while ( c->parent != NULL && c->parent->color == RED )//插入的元素一定为红，判断其父结点是否也为红，为红则不满足条件：红结点的子结点都为黑　
	{
		node* grandpa = c->parent->parent;
		if ( grandpa->left == c->parent )//插入的是左子树
		{
			node* uncle = grandpa->right;
			if ( uncle->color == RED )//叔父结点为红，将其父及叔父结点涂黑，祖父结点涂红
			{
				grandpa->color = RED;
				c->parent->color = BLACK;
				uncle->color = BLACK;
				c = grandpa;         //继续判断涂红的祖父结点是否满足红黑树要求
			}
			else if ( uncle->color == BLACK )//叔父结点为黑
			{
				if ( c == c->parent->right )//如果是右结点，则要变成左结点，应该只存在父结点的左结点为nil的情况
				{
					c = c->parent;
					left_rotate( c );
				}

				c->parent->color = BLACK;
				c->parent->parent->color = RED;
				right_rotate( c->parent->parent );//右旋，将当前结点的父结点变成袓父结点
			}
		}
		else
		{
			node* uncle = grandpa->left;
			if ( uncle->color == RED )
			{
				grandpa->color = RED;
				c->parent->color = BLACK;
				uncle->color = BLACK;
				c = grandpa;
			}
			else if ( uncle->color == BLACK )
			{
				if ( c == c->parent->left )
				{
					c = c->parent;
					right_rotate( c );
				}

				c->parent->color = BLACK;
				c->parent->parent->color = RED;
				left_rotate( c->parent->parent );
			}
		}
	}
	root->color = BLACK;
}

//与左旋相反
void rb_tree::right_rotate( node* c )
{
	if ( c->left != nil )
	{
		c->left->parent = c->parent;
		if ( c->parent != NULL )
		{
			if ( c->parent->left == c )
			{
				c->parent->left = c->left;
			}
			else
			{
				c->parent->right = c->left;
			}
		}
		else
		{
			root = c->left;
		}
		node* temp = c->left->right;
		c->parent = c->left;
		c->left->right = c;
		c->left = temp;
		if ( temp != nil )
		{
			temp->parent = c;
		}
	}
}

//当前结点的right存在，将right变成当前结点的父结点，当前结点变成right的左结点，right的左子树变成当前结点的右子树
void rb_tree::left_rotate( node* c )
{
	if ( c->right != nil )
	{
		c->right->parent = c->parent;
		if ( c->parent != NULL )
		{
			if ( c->parent->left == c )
			{
				c->parent->left = c->right;
			}
			else
			{
				c->parent->right = c->right;
			}
		}
		else
		{
			root = c->right;
		}
		node* temp = c->right->left;
		c->parent = c->right;
		c->right->left = c;
		c->right = temp;
		if ( temp != nil )
		{
			temp->parent = c;
		}
	}
}

//查找n的中序后继
rb_tree::node* rb_tree::successor( rb_tree::node* n )
{
	if ( n->right != nil )
	{
		node* temp = n->right;
		while ( temp->left != nil )
		{
			temp = temp->left;
		}
		return temp;
	}
	else
	{
		node* temp = n->parent;
		while ( temp->parent != NULL )
		{
			temp = temp->parent;
		}
		while ( temp->left != nil && temp->left != n )
		{
			temp = temp->left;
		}
		return temp;
	}
}

void rb_tree::delete_node( node* del )
{
	node* real_del = NULL;
	if ( del->left == nil || del->right == nil )
	{
		real_del = del;
	}
	else
	{
		real_del = successor( del );
	}
	
	node* child = NULL;
	if ( real_del->left != nil )
	{
		child = real_del->left;
	}
	else
	{
		child = real_del->right;
	}
	child->parent =real_del->parent;
	if ( real_del->parent == NULL )
	{
		root = child;
	}
	else
	{
		if ( child->parent->left == real_del )
		{
			child->parent->left = child;
		}
		else
		{
			child->parent->right = child;
		}
	}
	
	if ( real_del != del )
	{
		del->key = real_del->key;
	}

	if ( real_del->color == BLACK )
	{
		delete_fixup( child );
	}
}

void rb_tree::delete_fixup( node* child )
{
	node* temp = child;
	while ( temp != root && temp->color == BLACK )
	{
		if ( temp->parent->left == temp )
		{
			node* brother = temp->parent->right;
			if ( brother->color == RED )
			{
				brother->color=BLACK; 
				temp->parent->color=RED; 
				left_rotate( temp->parent );
				brother = temp->parent->right;
			}
			
			if ( brother->left->color == BLACK && brother->right->color == BLACK )
			{
				brother->color=RED; 
				temp=temp->parent; 
			}
			else if( brother->right->color == BLACK ) //case 3: brother的左子树是红色，右子树是黑色的话 
			{ 
				brother->color=RED; 
				brother->left->color=BLACK; 
				right_rotate( brother ); 
				brother=temp->parent->right; 
			} 
			brother->color=temp->parent->color; //case 4: brother的右子树是红色 
			temp->parent->color=BLACK; 
			brother->right->color=BLACK; 
			left_rotate( temp->parent); 

			temp=root; 
		} 
		else //对称情况，如果temp是其父结点的右子树 
		{ 
			node *brother=temp->parent->left; 
			if( brother->color == RED ) 
			{ 
				brother->color=BLACK; 
				temp->parent->color=RED; 
				right_rotate( temp->parent); 
				brother=temp->parent->left; 
			} 
			if( brother->left->color == BLACK && brother->right->color == BLACK ) 
			{ 
				brother->color=RED; 
				temp=temp->parent; 
			} 
			else if( brother->left->color == BLACK ) 
			{ 
				brother->color=RED; 
				brother->right->color=BLACK; 
				left_rotate(brother); 
				brother=temp->parent->left; 
			} 
			brother->color=temp->parent->color; 
			temp->parent->color=BLACK; 
			brother->left->color=BLACK; 
			right_rotate(temp->parent); 

			temp=root; 
		} 
	} 
	temp->color = BLACK;
}

bool rb_tree::remove( int value )
{
	if ( root == NULL )
		return false;

	node* temp = root;
	while ( temp != nil )
	{
		if ( temp->key > value )
		{
			temp = temp->left;
		}
		else if ( temp->key < value )
		{
			temp = temp->right;
		}
		else
		{
			delete_node( temp );
			return true;
		}
	}
	return false;
}
