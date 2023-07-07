#ifndef AVL_H
#define AVL_H

// DO NOT ADD OR REMOVE ANYTHING FROM THIS FILE

typedef struct AVLNode * AVLNodePtr;

// Use only this struct definition.
typedef struct AVLNode{
    AVLNodePtr child[2]; // child[0] is left, child[1] is right.
    int key, height, size; // size is the subtree size.
} AVLNode;


// AVL Operations

// delete the node with key <k> (if exists). Return a pointer to the new root.
AVLNodePtr avl_delete( AVLNodePtr tnode, int k );

// insert a new node with key <k> into the subtree (unless the key exists already). Return a pointer to the new root.
AVLNodePtr avl_insert( AVLNodePtr tnode, int k );

// return a new initialized avl node with key <k>. If malloc failed return NULL.
AVLNodePtr new_avl_node( int k );

// Free all nodes in the tree.
void delete_avl_tree( AVLNodePtr root );


// Queries

// search for a node with key <k> in the subtree and return the node if exists. Otherwise return NULL.
AVLNodePtr avl_search( AVLNodePtr tnode, int k );

// Return the rank of <k>. That is, the number of keys with value lower than or equal to k.
int avl_rank( AVLNodePtr tnode, int k );

// Return the rank of <k>. That is, the number of keys with value more than or equal to k.
int avl_reversed_rank( AVLNodePtr tnode, int k );

// given roots of AVL trees T1 and T2 (root1 and root2 resp.), and a joint node <xnode>
// such that keys(T1)<key(xnode)<keys(T2), avl_join joins all the three into a single AVL tree.
// Returns a pointer to the root of the newly formed tree.
AVLNodePtr avl_join( AVLNodePtr root1, AVLNodePtr xnode, AVLNodePtr root2 );

// Split an AVL tree rooted at <root>, according to a key <x> that also exists in the tree.
// The output is two AVL trees T0 and T1 such that keys(T0)<x<keys(T1), and also the node with key x.
// The node of x is returned by the function and the roots of T0 and T1 are placed in
// trees_out[0] and trees_out[1] respectively.
AVLNodePtr avl_split( AVLNodePtr root, int x, AVLNodePtr trees_out[2] );

// Return the median of the two avl trees (You may assume that the total size is odd).
int avls_median( AVLNodePtr t1, AVLNodePtr t2 );
#endif
