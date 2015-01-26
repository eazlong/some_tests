#include "test_func.h"

int find_kth_min_value( int* arr1, int size1, int* arr2, int size2, int k )
{
	if ( size1 > size2 ) //È·±£size1 < size2
		find_kth_min_value( arr2, size2, arr1, size1, k );
	if ( size1 == 0 )
		return arr2[k-1];
	if ( k == 1 )
		return min( arr1[0], arr2[0] );
	
	int k1 = min( size1, k/2 );
	int k2 = k - k1;
	if ( arr1[k1-1] < arr2[k2-1] )
	{
		return find_kth_min_value( arr1+k1, size1-k1, arr2, size2, k-k1 );
	}
	else if ( arr1[k1-1] > arr2[k2-1] )
	{
		return find_kth_min_value( arr1, size1, arr2+k2, size2-k2, k-k2 );
	}
	else
	{
		return arr1[k1-1];
	}
}

int mid_value_in_two_sorted_array( int* arr1, int size1, int* arr2, int size2 )
{
	if ( arr1 == NULL || size1 == 0 || arr2 == NULL || size2 == 0 )
		return -1;

	int count = size1+size2;
	int mid = (count&0x01)?(count/2+1):(count/2);
	return find_kth_min_value( arr1, size1, arr2, size2, mid );
}

void print_number( unsigned int digit );
void test_merge_list();
void test_complex_list_copy();
void test_mid_value()
{
	int* arr1 = NULL;
	int arr2[] = { 1, 8, 9, 12, 43, 88 };

	cout << "first test:" << mid_value_in_two_sorted_array( arr1, 0, arr2, sizeof(arr2)/sizeof(int) ) << endl;

	int arr3[] = { 8, 9, 100, 200, 340, 888, 999, 10000 };
	cout << "second test:" << mid_value_in_two_sorted_array( arr2, sizeof(arr2)/sizeof(int), arr3, sizeof(arr3)/sizeof(int) ) << endl;


	test_rebuild_tree();
	test_change_to_other();
	print_number( 2 );
	test_merge_list();
	test_complex_list_copy();
}

bool find_in_matrix( int* matrix, int rows, int colums, int find )
{
	if ( matrix == NULL || rows <= 0 || colums <= 0 )
		return false;

	int c = colums-1;
	while( c >= 0 )
	{
		if ( *(matrix+c) == find )
			return true;
		else if ( *(matrix+c) > find )
			c --;
		else
			break;
	}

	if ( c < 0 )
		return false;

	int r = rows-1;
	while( r >= 0 )
	{
		if ( *(matrix+r*colums) == find )
			return true;
		else if ( *(matrix+r*colums) > find )
			r --;
		else
			break;
	}
	
	if ( r < 0 )
		return false;

	for ( int i=0; i<c; i++ )
	{
		for ( int j=0; j<r; j++ )
		{
			if ( *(matrix+i*j) == find )
				return true;
		}
	}

	return false;
}

struct tree_node
{
	int value;
	tree_node* left;
	tree_node* right;
};

tree_node* rebuild_tree( int* front, int* mid, int size )
{
	if ( front == NULL || mid == NULL || size == 0 )
		return NULL;

	tree_node* root = new tree_node;
	root->left = NULL;
	root->right = NULL;
	root->value = front[0];

	if ( size == 1 )
		return root;

	int i=0;
	for ( ; i<size; i++ )
	{
		if ( mid[i]==front[0] )
			break;
	}

	root->left = rebuild_tree( front+1, mid, i );
	root->right = rebuild_tree( front+i+1, mid+i+1, size-i-1 );
	return root;
}
void convert_tree_to_list( tree_node* root, tree_node** last);

void test_rebuild_tree()
{
	int arr_front[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int arr_mid[] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	tree_node* root = rebuild_tree( arr_front, arr_mid, sizeof(arr_front)/sizeof(int) );
	tree_node* last = NULL;
	convert_tree_to_list( root, &last); 
}

int change_to_other( int src, int other )
{
	int xor = src^other;
	int count = 0;
	while ( xor )
	{
		count ++;
		xor = (xor-1)&xor;
	}
	return count;
}

void test_change_to_other()
{
	cout << change_to_other( 8, 7 ) << endl;
}

void print_number( unsigned int digit )
{
	char* num = new char[digit+1];
	memset( num, '0', digit );
	num[digit] = '\0';
	while ( true )
	{
		int i = digit-1;
		while ( true )
		{
			if ( num[i] == '9' )
			{
				num[i] = '0';
				i--;
				if ( i<0 )
					break;
			}
			else
			{
				num[i]++;
				break;
			}
		}
		if ( i<0 )
			break;
		cout << num << endl;
	}

	delete [] num;
}

struct list_node
{
	int value;
	list_node* next;
};

list_node* merge_list( list_node* list1, list_node* list2 )
{
	if ( list1 == NULL || list2 == NULL )
		return list1?list1:list2;
	
	list_node* merged = NULL;
	if ( list1->value<list2->value )
	{
		merged = list1;
		list1 = list1->next;
	}
	else
	{
		merged = list2;
		list2 = list2->next;
	}
	
	list_node* list3 = merged;
	while( list1 != NULL && list2 != NULL )
	{
		if ( list1->value<list2->value )
		{
			merged->next = list1;
			list1 = list1->next;
		}
		else
		{
			merged->next = list2;
			list2 = list2->next;
		} 
		merged = merged->next;
	}

	merged->next = (list1!=NULL) ? list1 : list2;
	return list3;
}

void test_merge_list()
{
	list_node* list1 = new list_node;
	list_node* temp = list1;
	for ( int i=0; i<10; i++ )
	{
		temp->value = i*10;
		temp->next = i==9?NULL:new list_node;
		temp = temp->next;
	}
	list_node* list2 = new list_node;
	temp = list2;
	for ( int i=0; i<5; i++ )
	{
		temp->value = i*5;
		temp->next = i==4?NULL:new list_node;
		temp = temp->next;
	}

	temp = merge_list(NULL, list2);

	while ( temp != NULL )
	{
		cout << temp->value << "->";
		temp = temp->next;
	}
	cout << endl;
}

struct complex_list_node
{
	int value;
	complex_list_node* next;
	complex_list_node* sibling;
};

complex_list_node* complex_list_copy( complex_list_node* src )
{
	if ( src == NULL )
		return NULL;

	complex_list_node* temp = src;
	while ( temp != NULL )
	{
		complex_list_node* new_node = new complex_list_node;
		new_node->value = temp->value;
		new_node->next =  temp->next;
		new_node->sibling = temp->sibling;
		temp->next = new_node;
		temp = new_node->next;
	}

	temp = src->next;
	while ( temp != NULL )
	{
		if ( temp->sibling != NULL )
		{
			temp->sibling = temp->sibling->next;
		}
		if ( temp->next == NULL )
		{
			break;
		}
		temp = temp->next->next;
	}
	
	temp = src;
	complex_list_node* dest = temp->next;
	while ( temp != NULL )
	{
		if ( temp->next == NULL )
			break;

		temp->next = temp->next->next;
		temp = temp->next;
	}

	return dest;
}

void convert_tree_to_list( tree_node* root, tree_node** last )
{
	if ( root == NULL )
		return;
	
	tree_node* temp = root;
	if ( temp->left != NULL )
	{
		convert_tree_to_list( temp->left, last );
	}

	temp->left = (*last);
	if ( *last != NULL )
		(*last)->right = temp;
	(*last) = temp;
	
	if ( temp->right != NULL )
	{
		convert_tree_to_list( temp->right, last );
	}
}

void permutation( char* str, char* start )
{
	if ( start == '\0' )
	{
		cout << str << endl;
		return;
	}
	
	for ( char* ch=start; *ch!='\0'; ++ch )
	{
		char temp = *ch;
		*ch = *start;
		*start = temp;

		permutation( str, ch );

		char temp = *ch;
		*ch = *start;
		*start = temp;
	}

}

void print_permutation( char* str )
{
	if ( str == NULL )
		return;

	permutation( str, str );
}

void test_complex_list_copy()
{
	complex_list_node* new_node1 = new complex_list_node;
	new_node1->value = 7;
	new_node1->next = NULL;
	new_node1->sibling = NULL;

	complex_list_node* new_node2 = new complex_list_node;
	new_node2->value = 6;
	new_node2->next = new_node1;
	new_node2->sibling = new_node1;

	complex_list_node* new_node3 = new complex_list_node;
	new_node3->value = 5;
	new_node3->next = new_node2;
	new_node3->sibling = new_node1;

	complex_list_node* new_node4 = new complex_list_node;
	new_node4->value = 4;
	new_node4->next = new_node3;
	new_node4->sibling = new_node2;

	complex_list_node* new_list = complex_list_copy( new_node4 );
	
	char data[] = "abcd";
	print_permutation( data );
}
