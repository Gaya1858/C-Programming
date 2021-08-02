///
/// File: bst.h
/// Binary Search Tree structure and function declarations 
///
/// @author: CS@RIT.EDU

#ifndef BST_H
#define BST_H

/// The definition of the tree structure
typedef struct TreeNode {
    int data ;                  ///< the data stored in the node
    struct TreeNode *left ;     ///< node's left child
    struct TreeNode *right ;    ///< node's right child
} TreeNode;

/// The three supported traversals
typedef enum {
    PREORDER,           ///< parent -> left -> right
    INORDER,            ///< left -> parent -> right
    POSTORDER           ///< left -> right -> parent
} TraversalType;

// FUNCTIONS STUDENTS ARE REQUIRED TO IMPLEMENT

/// tree_build
///     Dynamically build a BST by allocating nodes on the heap.
///     The client passes the address of storage that will hold
///     the pointer to the root tree node. The function then
///     dynamically allocates the nodes as it builds the binary
///     search tree which holds the elements.
///
/// @param rootptr - a pointer to the pointer to the root of the tree
///                  to build this tree onto.
/// @param data - array of integers to add to the tree
/// @param num  - the number of integers in the array

void tree_build( TreeNode **rootptr, const int data[], const int num );

/// tree_traverse
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// @param root - a pointer to the root of the tree to traverse
/// @param type - the traversal type

void tree_traverse( const TreeNode* root, const TraversalType type );

/// tree_destroy
///    Clean up all memory associated with the nodes in a BST.
///
/// @param root - the current root of the tree

void tree_destroy( TreeNode *root );

#endif // BST_H
