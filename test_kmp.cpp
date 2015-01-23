#include "test_func.h"

//查找下一个要比较的字符的下标，即查找最长的重复字符
//ababac
//001230
void get_next( const char* p, int next[], int count )
{
	if ( p == NULL || next == NULL || count == 0 )
	{
		cout << __FUNCTION__ << ":arg error!" << endl;
		return;
	}

	int i=0,j=1;
	memset( next, 0, sizeof(int)*count );

	while ( j < count )
	{
		if ( p[i] == p[j] )
		{
			next[j] = ++i; 
			j++;
		}
		else
		{
			j++;
			i=0;
		}
	}
}

//查找时
//abababacaad
//ababac                第一次比较到b时，出错
//     3　　　　　　　　从下标3开始
//     bac              

char* kmp( const char* src, const char* sub, int* next )
{
	if ( src == NULL || sub == NULL || next == NULL )
	{
		cerr << __FUNCTION__ << ": arg error!" << endl;
		return NULL;
	}
	
	int sub_len = strlen(sub);
	int src_len = strlen(src);
	int j=0;
	for ( int i=0; i<src_len;  )
	{
		if ( src[i] == sub[j] )
		{
			if ( ++j == sub_len )
				return (char*)(src+i-j+1);
			i++;
		}
		else
		{
			if ( j != 0 )
				j = next[j-1];
			else
				i++;
		}
	}

	return NULL;
}

void test_kmp()
{
	char* p = "ababac";
	unsigned int size = strlen( p );
	int *next = new int[size];
	get_next( p, next, size );
	cout << "get next for " << p << " is:" << endl;
	print_arrary<int>( next, size );

	getchar();

	char* src = "abababacaad";
	char* dest = kmp( src, p, next );
	if ( dest != NULL )
		cout << "search str for " << src << ":" << dest << endl;
	else 
		cout << "search str for " << src << " failed" << endl;
}