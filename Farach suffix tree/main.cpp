/*
	Text algorithms - Farach suffix tree implementation

	Krzysztof Parjaszewski - student, 4th year
	Institute of Computer Science, 
	Department of Mathematics and Computer Science
	University of Wroclaw
*/
#include <stdio.h>
#include "farach.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	int l = 1024;
	int * test1 = new int[l];
	srand(9128741);
	for(int i=0;i<l;i++){
		test1[i] *= rand();
		test1[i] %= 2*(rand()+1);
		test1[i] = abs(test1[i]);
	}
	int test2[] = {110,109,108,107,106,105,104,103,102,101};
	int test3[] = {18,18,37,37,9,9};
	int test4[] = {1,2,1,1,1,2,2,1,2,2,2,1};
	int test5[] = {'b','b','a','a','b','b','a','a','n','n','a','a','n','n','a','a'};
	// goal:      {2,1,4,3,6,5,8,7,10,9}
	//radix_sort_pairs(test1,l);
	//radix_sort_pairs(test2,10);
	//radix_sort_pairs(test3,6);
	int len = sizeof(test4)/sizeof(int);
	compute_suffix_tree(test4,len);
	return 0;
}

