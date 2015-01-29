#pragma once

#include <iostream>
using namespace std;

template<class T>
void print_arrary( T* arr, unsigned int count )
{
	for ( unsigned int i=0; i<count; i++ )
	{
		cout << arr[i];
		if ( i!= count-1 )
		{
			cout << "-";
		}
	}
	cout << endl;
}

void test_kmp();
void test_bm();

void test_qsort();
void test_shell();
void test_heap();
void test_merge();

void test_rb_tree();
void test_minimum_heap();

void test_mid_value();
void test_rebuild_tree();
void test_change_to_other();