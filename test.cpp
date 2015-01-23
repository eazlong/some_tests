#include <iostream>
#include <algorithm>

#include "test_func.h"

namespace __hidden__ 
{
	struct print
	{
		bool space;
		print() : space(false) {}
		~print() { std::cout << std::endl; }

		template <typename T>
		print &operator , (const T &t) 
		{
			if (space) std::cout << ' ';
			else space = true;
			std::cout << t;
			return *this;
		}
	};
}

#define print __hidden__::print(),

int sum( int *a, int n )
{
	return n==0?0:sum(a, n-1)+a[n-1];
}

void get_min_and_max( int* a, int n, int* min, int *max )
{
	//assert( a!=NULL && min != NULL && max != NULL );
	if ( n == 1 )
	{
		*min = std::min(*min, a[0]); 
		*max = std::max(*max, a[0]);
		return;
	}
	if ( n == 2 )
	{
		*min = std::min( std::min(a[0], a[1]), *min );
		*max = std::max( std::max(a[0], a[1]), *max );
		return;
	}
	
	int min_left = a[0], max_left = a[0];
	get_min_and_max( a, n/2, &min_left, &max_left );

	int min_right = a[0], max_right = a[0];
	get_min_and_max( a+n/2, n/2+(n%2), &min_right, &max_right );

	*min = std::min( min_left, min_right );
	*max = std::max( max_left, max_right );
}

int binary_search( int* src, int n, int value )
{
	if ( src == NULL )
	{
		return -1;
	}

	if ( n==1 )
	{
		if ( src[0]== value )
			return 0;
		else
			return -1;
	}
	
	if ( src[n/2]<value )
	{
		int pos = binary_search(src+(n+1)/2, (n-1)/2, value);
		return pos==-1?-1:pos+(n+1)/2;
	}
	else if ( src[n/2]>value)
	{
		int pos = binary_search(src, n/2, value);
		return pos==-1?-1:pos;
	}
	else
	{
		return n/2;
	}
}

int binary_search2( int* src, int n, int value )
{
	int start = 0, end = n;
	
	while ( start != end )
	{
		int mid = (start+end)/2;
		if ( src[mid] == value )
		{
			return mid;
		}
		else if ( src[mid] > value )
		{
			end = mid;
		}
		else
		{
			start = mid+1;
		}
	}
	return -1;
}

int binary_search_in_rotated( int* src, int n, int value )
{
	int start = 0, end = n;
	while ( start != end )
	{
		int mid = (start+end)/2;
		if ( src[mid] == value )
		{
			return mid;
		}
		else if ( src[mid] > src[start] )
		{
			if ( value < src[mid] && value >= src[start] )
			{
				end = mid;
			}
			else
			{
				start = mid+1;
			}
		}
		else if ( src[mid] < src[end] )
		{
			if (  value > src[mid] && value <= src[end-1] )
			{
				start = mid+1;
			}
			else
			{
				end = mid;
			}
		}
		else
		{
			start++;
		}
	}
	return -1;
}

//void get_max_and_secmax()
int main( int argc, char* argv ) 
{
// 	int a = 1, b = 2;
// 	print "this is a test";
// 	print "the sum of", a, "and", b, "is", a + b;
// 
// 	int a1[] = { 1, 2, 3, 4, 5, 6, 7 };
// 	std::cout << sum( a1, sizeof(a1)/sizeof(int) ) << std::endl;
// 
// 	int a2[] = { 1, 2, 3, 7, 9, 6, -1, 11, 4, 8 };
// 	int min, max;
// 	get_min_and_max( a2, sizeof(a2)/sizeof(int), &min, &max );
// 	std::cout << "min=" << min << " max=" << max << std::endl;
// 	
// 	int max=0, sec_max=0;
// 	get_max_and_secmax( a2, sizeof(a2)/sizeof(int), &max, &sec_max );
// 	getchar();	
	
// 	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
// 	cout << binary_search2( a, 7, 7 );
// 	
//  	int a1[] = { 1, 1, 1, 1, 1, 6, 7, 1};
// 	cout << binary_search_in_rotated( a1, 8, 6 ) << ":";

	while( 1 )
	{
		cout << "----------------------------------" << endl;
		cout << "Please select test func:" << endl;
		cout << "---------string search------------" << endl;
		cout << "1. kmp" << endl;
		cout << "2. bm" << endl;
		cout << "----------sort--------------------" << endl;
		cout << "3. quick sort" << endl;
		cout << "4. shell sort" << endl;
		cout << "5. heap sort" << endl;
		cout << "6. merge sort" << endl;
		cout << "----------data structure--------------" << endl;
		cout << "7. rb tree" << endl;

		int selected;
		cin >> selected;

		switch (selected)
		{
		case 1:
			test_kmp();
			break;
		case 2:
			test_bm();
			break;
		case 3:
			test_qsort();
			break;
		case 4:
			test_shell();
			break;
		case 5:
			test_heap();
			break;
		case 6:
			test_merge();
			break;
		case 7:
			test_rb_tree();
			break;
		case 8:
			test_mid_value();
			break;
		default:
			cout << "select error!" << endl;
			break;
		}

		getchar();
	}

	return 0;
}