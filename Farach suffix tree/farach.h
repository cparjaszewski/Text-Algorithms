#ifndef __FARACH_H__
#define __FARACH_H__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_MBCS)
typedef __int64 long64;
#else
typedef long long long64;
#endif

struct tree_node;

struct node_list {
	// A pointer to current node
	tree_node * node;

	// A pointer to the next node
	node_list * next;

	// A pointer to the next node
	node_list * prev;

	// has this node been visited during the last DFS?
	bool visited;

	// used while traversing through the tree with DFS
	node_list * current_child;

	// Constructor with given node
	node_list(tree_node * n);

	// Adds a new node to the queue 
	void add_node(tree_node * n);

	// Deletes a node from the queue 
	void delete_node();

	
};

struct tree_node {
	// Suffix Tree keeps its alphabet as integer
	int chr;

	// The parent node
	tree_node * parent;

	// Suffix link
	tree_node * sl;

	// A array of children
	node_list * first_child;

	// Pointer to the last child
	node_list * last_child;

	// Children counter
	int child_count;

	// the root node is specially signed
	bool is_root;

	// Auxiliary variable for the odd tree contruction, set by default to false
	bool odded;

	// the suffix array rank is important
	int rank;

	// lenght - sum of the edge lengths on the path from the root to this node
	int L;

	// Constructor for the root
	tree_node();

	// constructor with parent
	tree_node(tree_node * par, int character, int r, int L);

	// If the current node has no children - it is alread a leaf
	bool is_leaf();

	// When building a suffix tree from the suffix array is is only possible to 
	// add a child at the end of the children list
	node_list * add_next_child(int character, int r, int L);
};



struct suff_tree {
	// The farach tree string denoted as array of integers
	int * S;

	// The length of the string
	int len;

	// The ranks of all suffixes - useful temporary structure
	int * ranks;

	// An array of pointers to the leaves representing the suffixes
	tree_node ** leaves;

	// The root node
	tree_node * root;

	// Create an empty new tree
	suff_tree() {
		this->S = NULL;
		this->len = 0;
		this->root = NULL;
		this->ranks = NULL;
		this->leaves = NULL;
	}

	// Allocate memory for the new tree
	suff_tree(const int len) {
		this->len = len;
		this->leaves = new tree_node*[this->len];
		this->S = new int[this->len];
		this->ranks = new int[this->len];
		this->root = new tree_node();
	}
};
struct pair {
	int first;
	int second;
};


/* 
First call of computing function 
*/
suff_tree * suffix_tree(int * S, int len);
/*
Main procedure of the algorithm, returns the suffix tree for a string of given length
*/
suff_tree * compute_suffix_tree(const int * S, const int len);

/*
If the current length of integer string is small enough, it is possible to calculate its suffix tree ad hoc
*/
suff_tree * ad_hoc_suffix_tree(const int * S, const int len);

/*
Recursively builds the odd tree basing on given S and S'
*/
suff_tree * build_odd_tree(const int * S, suff_tree * TSPrim, const int len);

/*
Calculates the even tree basing on the given odd tree
*/
suff_tree * build_even_tree(const int * S, const suff_tree * odd_tree, const int len);

/*
Merging both odd and even tree
*/
suff_tree * merge(suff_tree *odd_tree, suff_tree * even_tree, const int len);

/*
Radix sorts the given string - basing on pairs, an returns S' - rank of <S[2*i],S[2*i+1]> on the sorted list.
*/
int * get_s_prim(const int * S, const int len);

/*
Returns the lcp array for the lexicographically sorted chain of leaves
*/
int * get_lcp_lex(const suff_tree * st);

/*
Least common prefix
*/
int lcp(const int * A, const int lenA, const int * B, const int lenB);

/*
Least common prefix when we know only than word ends on YEN integer
*/
int lcp(const int * A, const int * B);


/*
Radix sort given pairs of a given length, returns an array of positions to sort with
*/
int * radix_sort_pairs(pair ** pairs, const int len);

/*
Auxiliary function that prints the trie
*/
void print_trie(const int * S, suff_tree * st) ;

/* 
Prints the array collection
*/
void print_pairs(pair ** pairs, const int len);


#endif
