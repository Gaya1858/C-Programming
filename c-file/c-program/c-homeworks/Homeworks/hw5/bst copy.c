///
///  bst.c
///  Binary search tree.
///this class builds a binary tree
///Traverse the binary tree
///and destroy the memory it allocated
///
///  Created by Gayathri Kanagaraj on 10/5/20 GK4045
///

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
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

void tree_build( TreeNode **rootptr, const int data[], const int num ){

    for(int i =0; i<num; i++){
        struct TreeNode *temp,*p;
        temp = malloc(sizeof(TreeNode));
        temp->left =NULL;
        temp->right=NULL;
        temp->data=data[i];
        p =*rootptr;
        if(*rootptr == NULL){
            *rootptr =temp;
        }
        else{
            struct TreeNode *current;
            current =*rootptr;
            while(current!=NULL){
                p =current;
                if(temp ->data > current -> data){
                    current = current->right;
                }
                else{
                    current =current -> left;
                }
            }
            if(temp -> data > p -> data){
                p -> right = temp;
                
            }
            else if (temp -> data < p -> data){
                p-> left =temp;
            }
        }
    }    
}
/// tree_traverse
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// @param root - a pointer to the root of the tree to traverse
/// @param type - the traversal type

void tree_traverse( const TreeNode* root, const TraversalType type ){

/*
     * If the type is INORDER then it will
     * call recursively and display the datas
     */
    if(type == INORDER){
        if(root -> left){
            tree_traverse(root->left, INORDER);
        }
        printf("%d\n",root -> data);
        if(root -> right){
            tree_traverse(root->right, INORDER);
            
        }
    }
    /*
     * If the type is PREORDER then it will
     * call recursively and display the datas
     */
    if(type == PREORDER){
        printf("%d\n",root -> data);
        if(root -> left){
            tree_traverse(root->left, PREORDER);
        }
        if(root -> right){
            tree_traverse(root->right, PREORDER);
            
        }
    }
    /*
     * If the type is POSTORDER then it will
     * call recursively and display the datas
     */
    if(type == POSTORDER){
        
        if(root -> left){
            tree_traverse(root->left, POSTORDER);
        }
        if(root -> right){
            tree_traverse(root->right, POSTORDER);
            
        }
        printf("%d\n",root -> data);
    } 
}

/// tree_destroy
///    Clean up all memory associated with the nodes in a BST.
///
/// @param root - the current root of the tree
void tree_destroy( TreeNode *root ){
     /* if the root is not null then it recursively call roo-> left and root-> right 
      * and free the nodes */
     if(root!= NULL){
        if(root->left){
            tree_destroy(root->left);
        }
        if(root->right){
            tree_destroy(root->right);
        }
        free(root);
    }
}

