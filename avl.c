// Do not change the next 13 lines
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum Position {LEFT, RIGHT} Position;  // TIP: use this in your code!

int max( int x, int y ){
    return (x < y) ? y : x;
}

int abs( int x ){
    return (x < 0) ? -x : x;
}



// Utilities


//Input: pointer to an avl node.
//Output: the current size of the given node.
int updateSize(AVLNodePtr x)
{
    if (x == NULL)
    {
        return 0;
    }

    int siz = 1;
    if (x->child[LEFT] != NULL)
    {
        siz += x->child[LEFT]->size;
    }
    if (x->child[RIGHT] != NULL)
    {
        siz += x->child[RIGHT]->size;
    }

    return siz;
}

//Input: pointer to an avl node.
//Output: the current size of the given node.
int updateHeight (AVLNodePtr x)
{
    if (x == NULL)
    {
        return -1;
    }

    int heigh = 0;
    if (x->child[LEFT] != NULL)
    {
        heigh += x->child[LEFT]->height + 1;
    }

    if (x->child[RIGHT] != NULL)
    {
        if (heigh < x->child[RIGHT]->height + 1)
        {
            heigh = x->child[RIGHT]->height + 1;
        }
    }

    return heigh;
}

//Input: pointer to an avl node.
//Output: the function updates the node's size and height with the update functions.s
void updateBoth(AVLNodePtr x)
{
    x->height = updateHeight(x);
    x->size = updateSize(x);
}


//Input: pointers to the root of an avl tree and another node x in it.
//Output: returns the parent node of x.
AVLNodePtr findParent(AVLNodePtr tnode, AVLNodePtr x)
{
    if (tnode == NULL || x == NULL)
    {
        return NULL;
    }

    if (tnode->key == x->key)
    {
        return NULL;
    }

    if (tnode->key < x->key)
    {
        if (tnode->child[RIGHT] != NULL)
        {
            if (tnode->child[RIGHT]->key == x->key)
            {
                return tnode;
            }
            return findParent(tnode->child[RIGHT], x);
        }
    }

    if (tnode->child[LEFT] != NULL)
        {
            if (tnode->child[LEFT]->key == x->key)
            {
                return tnode;
            }
            return findParent(tnode->child[LEFT], x);
        }

        return NULL;
}


//Input: pointers to an avl node, x, and it's parent.
//Output: RIGHT is x is the right child of it's parent and LEFT otherwise.
Position findPosition(AVLNodePtr x, AVLNodePtr px)
{
    if (px->child[RIGHT] != NULL)
    {
        if (px->child[RIGHT] == x)
        {
            return RIGHT;
        }
    }
    return LEFT;
}


//Input: pointer to an AVL node x and a position.
//Output: the function right-rotates x if the given position is RIGHT
//or left-rotates it if the given position is LEFT.
//The function returns the new node in x's place (or x if the rotation wasn't possible)
AVLNodePtr rotate(AVLNodePtr x, Position pos) {
    if (x == NULL)
    {
        return NULL;
    }

    Position pos2 = (pos == LEFT) ? RIGHT : LEFT;
    AVLNodePtr y = x->child[pos2];

    if (y == NULL) {
        return x;
    }

    x->child[pos2] = y->child[pos];
    y->child[pos] = x;

    updateBoth(x);

    updateBoth(y);
    return y;
}

///works ;)
//Input: pointer to a node from an avl tree.
//Output: the function balances the node, if it was unbalanced, and returns x or the node that replaced places with x.
AVLNodePtr balance(AVLNodePtr x)
{
    if (abs(updateHeight(x->child[LEFT]) - updateHeight(x->child[RIGHT])) <= 1)
    {
        return x;
    }

    AVLNodePtr y;
    if (updateHeight(x->child[LEFT]) > updateHeight(x->child[RIGHT]))
    {
        y = x->child[LEFT];
        if (y != NULL)
        {
            if (updateHeight(y->child[LEFT]) < updateHeight(y->child[RIGHT]))
            {
                y = rotate(y, LEFT);
                updateBoth(y);
                x->child[LEFT] = y;
                updateBoth(x);
            }
        }
        return rotate(x, RIGHT);
    }

    else
    {
        y = x->child[RIGHT];
        if (y != NULL)
        {
            if (updateHeight(y->child[RIGHT]) < updateHeight(y->child[LEFT]))
            {
                y = rotate(y, RIGHT);
                updateBoth(y);
                x->child[RIGHT] = y;
                updateBoth(x);
            }
        }
        return rotate(x, LEFT);
    }
}


//Input: pointers to the root of an avl rank tree and another node from it.
//Output: the function balances every unbalanced node between the root and the other node
//and returns the updated root.
AVLNodePtr balancePath(AVLNodePtr tnode, AVLNodePtr x)
{
    if (tnode == NULL)
    {
        return NULL;
    }

    if (x == NULL)
    {
        return tnode;
    }

    if (tnode->key > x->key)
    {
        tnode->child[LEFT] = balancePath(tnode->child[LEFT], x);
    }
    else if (tnode->key < x->key)
    {
        tnode->child[RIGHT] = balancePath(tnode->child[RIGHT], x);
    }

    return balance(tnode);
}


// Input: pointers to the root of an AVL tree and another node, x, from that tree, which has no right child.
// Output: the successor node of x.
AVLNodePtr successorCase(AVLNodePtr root, AVLNodePtr tnode, AVLNodePtr x)
{
    if (tnode == NULL || tnode == x) {
        return NULL;
    }

    if (tnode->key < x->key) {
        return successorCase(root, tnode->child[RIGHT], x);
    } else if (tnode->key > x->key) {
        AVLNodePtr s = successorCase(root, tnode->child[LEFT], x);
        if (s == NULL && tnode->child[RIGHT] == NULL) {
            return tnode;
        }
        return s;
    }

    AVLNodePtr s = tnode->child[RIGHT];
    while (s != NULL && s->child[LEFT] != NULL) {
        s = s->child[LEFT];
    }
    return s;
}

// Input: pointers to the root of an AVL tree and a node from it.
// Output: the successor of the given node.
AVLNodePtr successor(AVLNodePtr tnode, AVLNodePtr x)
{
    if (tnode == NULL || x == NULL) {
        return NULL;
    }

    if (x->child[RIGHT] != NULL) {
        AVLNodePtr y = x->child[RIGHT];
        while (y->child[LEFT] != NULL) {
            y = y->child[LEFT];
        }
        return y;
    }

    return successorCase(tnode, tnode, x);
}



//Input: a pointer to the root of an AVL tree and an integer k.
//Output: the function return a pointer from the given key whom key is closest to k.
AVLNodePtr closest(AVLNodePtr tnode, int k)
{
    if (tnode == NULL)
    {
        return NULL;
    }

    if (tnode->key == k)
    {
        return tnode;
    }

    if (tnode->key > k)
    {
        if (tnode->child[LEFT] == NULL)
        {
            return tnode;
        }
        return closest(tnode->child[LEFT], k);
    }

    else
    {
        if (tnode->child[RIGHT] == NULL)
        {
            return tnode;
        }
        return closest(tnode->child[RIGHT], k);
    }
}


//Input: a pointer to the root of an avl rank tree.
//Output: the biggest key from that tree.
int maxKey(AVLNodePtr tnode)
{
    if (tnode == NULL)
    {
        return 0;
    }

    if (tnode->child[RIGHT] != NULL)
    {
        return maxKey(tnode->child[RIGHT]);
    }
    return tnode->key;
}


//Input: a pointer to the root of an avl rank tree.
//Output: the smallest key from that tree.
int minKey(AVLNodePtr tnode)
{
    if (tnode == NULL)
    {
        return 0;
    }

    if (tnode->child[LEFT] != NULL)
    {
        return minKey(tnode->child[LEFT]);
    }
    return tnode->key;
}


//The same as avl_insert, but it inserts an existing external node instead of an integer.
AVLNodePtr avl_insert_node( AVLNodePtr tnode, AVLNodePtr x ){
    if (tnode == NULL)
    {
        return x;
    }
        if (avl_search(tnode, x->key) != NULL)
    {
        return tnode;
    }

    if (tnode->key > x->key)
    {
        tnode->child[LEFT] = avl_insert_node(tnode->child[LEFT], x);
    }

    if (tnode->key < x->key)
    {
        tnode->child[RIGHT] = avl_insert_node(tnode->child[RIGHT], x);
    }

    tnode = balance(tnode);
    updateBoth(tnode);
    return tnode;
}


//Input: a pointer to the root of an AVL node.
//Output: the given node's key or 0 it the node does not exist.
int keyOrZero(AVLNodePtr tnode)
{
    if (tnode != NULL)
    {
        return tnode->key;
    }
    return 0;
}


//Input: pointers to the root of an AVL rank tree and another node xNode and an array of node pointers.
//Output: the function adds all of the given tree's nodes that have keys smaller then xNode's to the first
//pointer of the array and all of the nodes with keys bigger then xNode's key to the second pointer
//of the array.
void buildSplit(AVLNodePtr t, AVLNodePtr xNode, AVLNodePtr trees_out[2]) {
    if (t == NULL) {
        return;
    }

    if (t->key < xNode->key) {
        buildSplit(t->child[RIGHT], xNode, trees_out);
        t->child[RIGHT] = trees_out[0];
        trees_out[0] = t;
    } else if (t->key > xNode->key) {
        buildSplit(t->child[LEFT], xNode, trees_out);
        t->child[LEFT] = trees_out[1];
        trees_out[1] = t;
    } else {
        trees_out[0] = t->child[LEFT];
        trees_out[1] = t->child[RIGHT];
        t->child[LEFT] = NULL;
        t->child[RIGHT] = NULL;
    }

    updateBoth(t);
}


// Operations

//Input: pointer to the root of an AVL rank tree and an integer k.
//Output: the function inserts a new node with k as it's key
//to the given tree and returns the updated root after balancing.
AVLNodePtr avl_insert( AVLNodePtr tnode, int k ){
    if (tnode == NULL)
    {
        return new_avl_node(k);
    }
        if (avl_search(tnode, k) != NULL)
    {
        return tnode;
    }

    if (tnode->key > k)
    {
        tnode->child[LEFT] = avl_insert(tnode->child[LEFT], k);
    }

    if (tnode->key < k)
    {
        tnode->child[RIGHT] = avl_insert(tnode->child[RIGHT], k);
    }

    tnode = balance(tnode);
    updateBoth(tnode);
    return tnode;
}


//Input: pointer to the root of and AVL node tree and an integer k
//which is a key from that tree.
//Output: the function deletes the node with k equal to k
//and returns the updated after balancing.
AVLNodePtr avl_delete(AVLNodePtr tnode, int k) {
    if (tnode == NULL) {
        return NULL;
    }

    AVLNodePtr x = avl_search(tnode, k);

    if (x == NULL) {
        return tnode;
    }

    AVLNodePtr px, y;

    if (x->child[LEFT] == NULL && x->child[RIGHT] == NULL) {
        px = findParent(tnode, x);
        if (px != NULL) {
            px->child[findPosition(x, px)] = NULL;
            free(x);
            return balancePath(tnode, px);
        }
        else
        {
            free(x);
            return NULL;
        }
    }

    if (x->child[LEFT] == NULL) {
        px = findParent(tnode, x);
        if (px != NULL) {
            px->child[findPosition(x, px)] = x->child[RIGHT];
            free(x);
            return balancePath(tnode, px);
        }
        else
        {
            tnode = x->child[RIGHT];
            free(x);
            return balance(tnode);
        }
    }

    if (x->child[RIGHT] == NULL) {
        px = findParent(tnode, x);
        if (px != NULL) {
            px->child[findPosition(x, px)] = x->child[LEFT];
            free(x);
            return balancePath(tnode, px);
        }
        else
        {
            tnode = x->child[LEFT];
            free(x);
            return balance(tnode);
        }
    }

    y = successor(tnode, x);
    x->key = y->key;
    y->key = k;
    return avl_delete(tnode, k);
}


//Input: the function gets an integer.
//Output: the function creates a new avl rank node, with a key equal to the given integer
//and returns it.
AVLNodePtr new_avl_node( int k ){
    AVLNodePtr x = (AVLNodePtr)malloc(sizeof(AVLNode));
    x->key = k;
    x->size = 1;
    x->height = 0;
    x->child[LEFT] = NULL;
    x->child[RIGHT] = NULL;

    return x;
}


//Input: pointer to the root of an AVL rank tree.
//Output: the function deletes and frees all of the nodes
//from that tree.
void delete_avl_tree( AVLNodePtr root ){
    if (root == NULL)
    {
        return;
    }

    delete_avl_tree(root->child[RIGHT]);
    delete_avl_tree(root->child[LEFT]);

    if (root->child[LEFT] == NULL && root->child[RIGHT] == NULL)
    {
        free(root);
    }
}


// Queries

//Input: pointer to the root of an AVL rank tree and an integer k.
//Output: pointer to a node from the given tree with a key equal
//to k, or NULL if it doesn't exist.
AVLNodePtr avl_search( AVLNodePtr tnode, int k ){
    if (tnode == NULL)
    {
        return NULL;
    }

    if (tnode->key == k)
    {
        return tnode;
    }
    if (tnode->key < k)
    {
        if (tnode->child[RIGHT] == NULL)
        {
            return NULL;
        }
        return avl_search(tnode->child[RIGHT], k);
    }

    if (tnode->child[LEFT] == NULL)
    {
        return NULL;
    }
    return avl_search(tnode->child[LEFT], k);
}


//Input: pointer to the root of an AVL tree and an integer k.
//Output: the function returns the number of keys from that
//tree who are smaller or equal to k.
int avl_rank( AVLNodePtr tnode, int k ){
    if (tnode == NULL)
    {
        return 0;
    }

    if (tnode->key > k)
    {
        if (tnode->child[LEFT] == NULL)
        {
            return 0;
        }
        return avl_rank(tnode->child[LEFT], k);
    }

    else
    {
        if (tnode->child[LEFT] == NULL && tnode->child[RIGHT] == NULL)
        {
            return 1;
        }
        if (tnode->child[LEFT] == NULL)
        {
            return 1 + avl_rank(tnode->child[RIGHT], k);
        }
        if (tnode->child[RIGHT] == NULL)
        {
            return 1 + tnode->child[LEFT]->size;
        }
        return 1 + tnode->child[LEFT]->size + avl_rank(tnode->child[RIGHT], k);
    }
}


//Input: pointer to the root of an AVL tree and an integer k.
//Output: the function returns the number of keys from that
//tree who are bigger or equal to k.
int avl_reversed_rank( AVLNodePtr tnode, int k ){
  if (tnode == NULL)
    {
        return 0;
    }

    if (tnode->key < k)
    {
        if (tnode->child[RIGHT] == NULL)
        {
            return 0;
        }
        return avl_reversed_rank(tnode->child[RIGHT], k);
    }

    else
    {
        if (tnode->child[LEFT] == NULL && tnode->child[RIGHT] == NULL)
        {
            return 1;
        }
        if (tnode->child[RIGHT] == NULL)
        {
            return 1 + avl_reversed_rank(tnode->child[LEFT], k);
        }
        if (tnode->child[LEFT] == NULL)
        {
            return 1 + tnode->child[RIGHT]->size;
        }
        return 1 + tnode->child[RIGHT]->size + avl_reversed_rank(tnode->child[LEFT], k);
    }
}


//Input: pointers to the roots of two AVL rank tree and an external node xnode, when the keys of the
//second tree are all bigger
//Output: the function returns an AVL rank tree containing all the given node
//and every node from the two trees.
AVLNodePtr avl_join(AVLNodePtr root1, AVLNodePtr xnode, AVLNodePtr root2) {
    if (root1 == NULL)
    {
        return avl_insert_node(root2, xnode);
    }

    if (root2 == NULL)
    {
        return avl_insert_node(root1, xnode);
    }

    if (abs(updateHeight(root1) - updateHeight(root2)) <= 1)
    {
        xnode->child[LEFT] = root1;
        xnode->child[RIGHT] = root2;
        return xnode;
    }

    int higher;
    if (root1->height > root2->height)
    {
        higher = 1;
    }
    else
    {
        higher = 2;
    }

    AVLNodePtr y, py;
    int stop = 0;
    if (higher == 1)
    {
        y = root1;
        while(y != NULL && stop == 0)
        {
            if (y->height - root2->height <= 1)
            {
                stop = 1;
            }
            else
            {
                y = y->child[RIGHT];
            }
        }

        py = findParent(root1, y);
        py->child[RIGHT] = xnode;
        xnode->child[RIGHT] = root2;
        xnode->child[LEFT] = y;

        root1 = balancePath(root1, py);
    }
        else
        {
        y = root2;
        while(y != NULL && stop == 0)
        {
            if (y->height - root1->height <= 1)
            {
                stop = 1;
            }
            else
            {
                y = y->child[LEFT];
            }
        }

        py = findParent(root2, y);
        py->child[LEFT] = xnode;
        xnode->child[LEFT] = root1;
        xnode->child[RIGHT] = y;

        return balancePath(root2, py);
    }
}


//Input: pointer to the root of an AVL rank tree, an integer that's a key from said tree and an array of 2 avl node pointers.
//Output: the function returns a node with x's key and adds all of the nodes from the tree with keys smaller than
//the integer to the first tree of the array and all of the nodes with keys bigger then x's key
//to the second tree.
AVLNodePtr avl_split(AVLNodePtr tnode, int x, AVLNodePtr trees_out[2]) {
    trees_out[0] = NULL;
    trees_out[1] = NULL;

    if (tnode == NULL) {
        return NULL;
    }

    AVLNodePtr xNode = avl_search(tnode, x);

    if (xNode == NULL) {
        return NULL;
    }

    if (x == tnode->key) {
        trees_out[0] = xNode->child[LEFT];
        trees_out[1] = xNode->child[RIGHT];
        xNode->child[LEFT] = NULL;
        xNode->child[RIGHT] = NULL;
        return xNode;
    }

    if (x == maxKey(tnode)) {
        trees_out[0] = avl_delete(tnode, x);
        trees_out[1] = NULL;
        return new_avl_node(x);
    } else if (x == minKey(tnode)) {
        trees_out[0] = NULL;
        trees_out[1] = avl_delete(tnode, x);
        return new_avl_node(x);
    }

    buildSplit(tnode, xNode, trees_out);
    return xNode;
}


//Input: pointers to two roots of AVL rank trees, where the sum
//of their sizes is odd.
//Output: the function returns pointer to the median node
//of all the nodes from the trees.
AVLNodePtr avl_median( AVLNodePtr t1, AVLNodePtr t2 ){
    if (t1 == NULL && t2 == NULL)
    {
        return NULL;
    }

    int wanted = (int)(updateSize(t1) + updateSize(t2))/2 + 1;

    AVLNodePtr x = t1;
    AVLNodePtr closes = NULL;
    int ranks = 0;
    int stop = 0;

    while (x != NULL && stop == 0)
    {
        ranks = 0;
        ranks += avl_rank(t1, x->key);
        closes = closest(t2, x->key);
        ranks += avl_rank(t2, closes->key);
        if (closes->key > x->key)
        {
            ranks = ranks - 1;
        }

        if (wanted == ranks)
        {
            stop = 1;

        }
        else
        {
            if (ranks < wanted)
            {
                x = x->child[RIGHT];
            }
            else
            {
                x = x->child[LEFT];
            }
        }
    }

    if (stop == 1)
    {
        return x;
    }

    stop = 0;
    x = t2;
    while (x != NULL && stop == 0)
    {
        ranks = 0;
        ranks += avl_rank(t2, x->key);
        closes = closest(t1, x->key);
        ranks += avl_rank(t1, closes->key);
        if (closes->key > x->key)
        {
            ranks = ranks -1;
        }

        if (wanted == ranks)
        {
            stop = 1;

        }
        else
        {
            if (ranks < wanted)
            {
                x = x->child[RIGHT];
            }
            else
            {
                x = x->child[LEFT];
            }
        }
    }
    if (stop == 1)
    {
        return x;
    }

    return NULL;
}


int main(){
    return 0;

}

