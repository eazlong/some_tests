#include "test_func.h"

void swap( int* a, int* b )
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

bool quick_sort( int arr[], int count )
{
	if ( arr == NULL )
	{
		return false;
	}

	if ( count == 0 || count == 1 )
	{
		return true;
	}

	int key = arr[count-1];              //选定key
	int j = count - 1;
	for ( int i=0; i<j; i++ )
	{
		if ( arr[i] <= key )
			continue;
		arr[j] = arr[i];                //将较大的数付右边

		while ( --j > i )
		{
			if ( arr[j]<key )
			{
				arr[i] = arr[j];       //将较小的数付左边
				break;
			}
		}
	}
	arr[j] = key;

	if ( !quick_sort( arr, j ) )
		return false;
	
	if ( !quick_sort( arr+j+1, count-j-1 ) )
		return false;

	return true;
}

void test_qsort()
{
	int a1[] = {1};
	int size1 = sizeof(a1)/sizeof(int);
	print_arrary( a1, size1 );
	quick_sort( a1, size1 );
	print_arrary( a1, size1 );

	int a2[] = {1, 35, 7, 99, 2, 44, 6, 8, 10};
	int size2 = sizeof(a2)/sizeof(int);
	print_arrary( a2, size2 );
	quick_sort( a2, size2 );
	print_arrary( a2, size2 );

	int a3[] = {1, 1, 1, 1, 2, 1, 0, 1, 10};
	int size3 = sizeof(a3)/sizeof(int);
	print_arrary( a3, size3 );
	quick_sort( a3, size3 );
	print_arrary( a3, size3 );
}

bool insert_sort( int arr[], int count )
{
	if ( arr==NULL || count == 0 )
		return false;

	for ( int i=1; i<count; i++ )
	{
		int key = arr[i];
		int j=i-1;
		for ( ; j>=0 && arr[j]>key; j-- )
		{
			arr[j+1] = arr[j];
		}
		arr[j+1] = key;
	}
	return true;
}

bool shell_insert_sort( int arr[], int count, int interval )
{
	if ( count<= interval || arr == NULL )
		return false;
	
	for ( int i=interval; i<count; i++ )
	{
		int key = arr[i];
		int j=i-interval;
		for ( ; j>=0 && arr[j]>key; j-=interval )
		{
			arr[j+interval] = arr[j];
		}
		arr[j+interval] = key;
	}

	print_arrary( arr, count );
	return true;
}
 
bool shell_sort( int arr[], int count )
{
	if ( arr == NULL || count == 0 )
		return false;

	int interval = count>>1;
	while ( interval >= 1 )
	{
		shell_insert_sort( arr, count, interval );
		interval >>= 1;
	}
	return true;
}


void test_shell()
{
	int a1[] = {1};
	int size1 = sizeof(a1)/sizeof(int);
	print_arrary( a1, size1 );
	shell_sort( a1, size1 );
	print_arrary( a1, size1 );

	int a2[] = {1, 35, 7, 99, 2, 44, 6, 8, 10};
	int size2 = sizeof(a2)/sizeof(int);
	print_arrary( a2, size2 );
	shell_sort( a2, size2 );
	print_arrary( a2, size2 );

	int a3[] = {1, 1, 1, 1, 2, 1, 0, 1, 10};
	int size3 = sizeof(a3)/sizeof(int);
	print_arrary( a3, size3 );
	shell_sort( a3, size3 );
	print_arrary( a3, size3 );
}

//选取根及其孩子结点中最大的放入根，然后继续（大根堆）
void shift( int arr[], int count, int k )
{
	if ( arr == NULL || count == 0 )
		return;

	int i=k;
	int j=2*k+1;
	while ( j < count )
	{
		if ( (j+1<count) && arr[j] < arr[j+1]  )
		{
			j ++;
		}
		if ( arr[i] < arr[j] )
		{
			swap( arr+i, arr+j );
			i = j;
			j = 2*i+1;
		}
		else
		{
			break;
		}
	}
}

bool heap_sort( int arr[], int count )
{
	if ( arr == NULL || count == 0 )
		return false;
	
	//构建大根堆
	for ( int i=count>>1; i>=0; i-- )
	{
		shift( arr, count, i );
	}

	cout << "small-root-heap:" << endl;
	print_arrary( arr, count );

	for ( int i=count-1; i>0; i-- )
	{
		swap( arr+i, arr );
		shift( arr, i, 0 );
		print_arrary( arr, count );
	}
	return true;
}

void test_heap()
{
	int a1[] = {1};
	int size1 = sizeof(a1)/sizeof(int);
	print_arrary( a1, size1 );
	heap_sort( a1, size1 );
	print_arrary( a1, size1 );

	int a2[] = {1, 35, 7, 99, 2, 44, 6, 8, 10};
	int size2 = sizeof(a2)/sizeof(int);
	print_arrary( a2, size2 );
	heap_sort( a2, size2 );
	print_arrary( a2, size2 );

	int a3[] = {1, 1, 1, 1, 2, 1, 0, 1, 10};
	int size3 = sizeof(a3)/sizeof(int);
	print_arrary( a3, size3 );
	heap_sort( a3, size3 );
	print_arrary( a3, size3 );
}

//合并，将两块数据合并到临时数组，再拷回去
void merge( int arr[], int count, int pos )
{
	if ( arr == NULL || count == 0 )
		return;

	int *temp = new int[count];
	int temp_pos = 0;
	int i=0, j=pos;
	while (  i<pos&&j<count )
	{
		if ( arr[i] < arr[j] )
		{
			temp[temp_pos++] = arr[i++];
		}
		else
		{
			temp[temp_pos++] = arr[j++];
		}
	}
	
	while ( i< pos )
	{
		temp[temp_pos++] = arr[i++];
	}

	while ( j<count )
	{
		temp[temp_pos++] = arr[j++];
	}
	
	memcpy( arr, temp, count*sizeof(int) );
	delete temp;
}

bool merge_sort( int arr[], int count )
{
	if ( arr == NULL || count == 0 )
		return false;

	if ( count == 1 )
	{
		return true;
	}

	merge_sort( arr, count/2 );
	merge_sort( arr+count/2, (count+1)/2 );
	merge( arr, count, count/2 );

	return true;
}

void test_merge()
{
	int a1[] = {1};
	int size1 = sizeof(a1)/sizeof(int);
	print_arrary( a1, size1 );
	merge_sort( a1, size1 );
	print_arrary( a1, size1 );

	int a2[] = {1, 35, 7, 99, 2, 44, 6, 8};
	int size2 = sizeof(a2)/sizeof(int);
	print_arrary( a2, size2 );
	merge_sort( a2, size2 );
	print_arrary( a2, size2 );

	int a3[] = {1, 1, 1, 1, 2, 1, 0, 1, 10};
	int size3 = sizeof(a3)/sizeof(int);
	print_arrary( a3, size3 );
	merge_sort( a3, size3 );
	print_arrary( a3, size3 );
}