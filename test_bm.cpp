#include "test_func.h"

//坏字符数组，即计算遇到坏字符时，需要移动的位，即　模式字符串长度－每个字符在模式串最后一次出现的位置-1
//ababc
//b 1 a 2 c 5
bool get_bmbc( const char* pattern, int* bmbc )
{
	if ( pattern == NULL || bmbc == NULL )
	{
		return false;
	}
	
	int len_pattern = strlen( pattern );
	for ( int i=0; i<256; i++ )
	{
		bmbc[i] = len_pattern;
	}

	int k = len_pattern-2;
	while ( k>=0 )
	{
		if ( *(bmbc+(unsigned char)(pattern[k])) == len_pattern )
		{
			*(bmbc+(unsigned char)(pattern[k])) = len_pattern - k - 1; 
		}

		k--;
	}
	
	return true;
}

//从右往左查找每一个字符左边与后缀相同的字符最大个数,最后固定为字符串长度
// ababcabab
// 020400209
bool get_suffix( const char* pattern, int* suffix )
{
	if ( pattern == NULL || suffix == NULL )
		return false;

	int len_pattern = strlen( pattern );
	suffix[len_pattern-1] = len_pattern;

	for ( int pos=len_pattern-2; pos >= 0 ; pos -- )
	{
		int cur = pos;
		while ( cur>=0 && pattern[cur] == pattern[len_pattern-1-pos+cur] )
		{
			cur--;
		}
		suffix[pos] = pos-cur;
	}

	return true;
}

//查找好后缀
bool get_bmgs( const char* pattern, int* bmgs )
{
	if ( pattern == NULL || bmgs == NULL )
	{
		return false;
	}

	int *suffix = new int[strlen(pattern)];
	if( !get_suffix( pattern, suffix ) )
	{
		return false;
	}
	cout << "get suffix for "<< pattern << endl;
	print_arrary<int>(suffix, strlen(pattern));
	
	int len_pattern = strlen(pattern);
	for ( int i=0; i<len_pattern; i++ )
	{
		bmgs[i] = len_pattern;
	}

	cout << "get bmgs for step 1:" << endl;
	print_arrary<int>(bmgs, strlen(pattern));

	//aabcbaaa　suffix:12000128 前缀情况
	//bmgs 66666679
	int j=0;
	for ( int i=len_pattern-2; i>=0; i-- )
	{
		if ( suffix[i] == i+1 )
		{
			for ( ; j<len_pattern-1-i; j++ )
			{
				if ( bmgs[j]==len_pattern )
				{
					bmgs[j] = len_pattern-1-i;
				}
			}
		}
	}
	cout << "get bmgs for step 2:" << endl;
	print_arrary<int>(bmgs, strlen(pattern));
	
	//匹配的情况
	//ddaaabcbaaa
	for (int i = 0; i <= len_pattern-2; ++i)  
	{
		bmgs[len_pattern - 1 - suffix[i]] = len_pattern - 1 - i; 
	}

	cout << "get bmgs for step 3:" << endl;
	print_arrary<int>(bmgs, strlen(pattern));

	return true;
}

void test_bm()
{
	const char* pattern = "adaaabcbaaa";
	int bmbc[256];
	if ( !get_bmbc( pattern, bmbc ) )
		return;

	print_arrary<int>( bmbc, 256 );

	unsigned int len_pattern = strlen(pattern);
	int *bmgs = new int[len_pattern];
	get_bmgs( pattern, bmgs );

	print_arrary<int>( bmgs, len_pattern );
	char* src = "1112cababcaba**abccaba*baceeababa";

	int len_src = strlen(src);
	unsigned int k = 0;
	while( k < len_src-len_pattern )
	{
		int j=len_pattern-1;
		for ( ; j>=0 && src[k+j] == pattern[j]; j-- )
		{
		}

		if ( j<0 )
		{
			cout << src+k << endl;
			break;
		}
		else
		{
			//bmbc[src[j + k]]-(len_pattern-1-j) 遇到坏字符时应移动的位数－已移动的位数
			int max_add = max( bmgs[j], bmbc[src[j + k]]-((int)len_pattern-1-j) );
			k += max_add;
		}
	}
}