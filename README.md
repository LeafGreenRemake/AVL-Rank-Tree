# AVL-Rank-Tree
An implementation of an AVL rank tree, with basic operations and extra, helpful new operations.
ALL of the operation were tested on regular and extreme cases.
All the operation's actions are explained inside the program.


List of standart operation; maxKey(tnode), maxKey(tnode), avl_insert_node(tnode, x), 
avl_delete(tnode, x), successor(tnode, x), new_avl_node(k), avl_search(tnode, k),
avl_rank(tnode, k), avl_join(root1, xnode, root2), avl_split(tnode, x, trees_out[2])

List of extra operations; updateSize(x), updateHeight(x), findParent(tnode, x), 
findPosition(x, px), balancePath(tnode, x), closest(tnode, k), delete_avl_tree(root), 
avl_reversed_rank(tnode, k), avl_median(t1, t2)


note; the program also contains smaller helper-functions for these bigger operations.
Also, make sure to use avl.h as an header file. It includes the structure of this program's tree nodes.
