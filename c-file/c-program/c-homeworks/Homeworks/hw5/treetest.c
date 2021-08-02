///
///  treetest.c
///  main function
///  reads user input and passes values to the bst.c functions.
///  displays Inorder, Preorder and Postorder value.
///
///  Created by Gayathri Kanagaraj on 10/5/20 GK4045
///

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/// output a usage message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void usage( char message[]) {
    fprintf( stderr, "%s", message );
}
/// output a note message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void error( char message[] ) {
    fprintf( stderr, "%s", message );
}
/// output a note message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param argc number of command line arguments
/// @param argv array of values of command line argument
/// @return int  EXIT-SUCCESS if successful completiion or EXIT _ERROR for for error.

int main(int argc, const char * argv[]) {
    
    if ( argc >1){
        int count = atoi(argv[1]);
        if(count >0){
            printf("Enter %d integer values to place in tree:\n",count);
            int value[count];
            int i =0;
            while(i<count){
                
                scanf("%d",&value[i]);
                i++;
            }
            i =0;
            printf("Input values:\n");
            for(i =0; i<count; i++){
                printf("%d\n",value[i]);
            }
	    struct TreeNode *root =NULL; /* root node created as null*/
            tree_build( &root, value, count);/*building a binary search tree*/
	    printf("Preorder:\n");
            tree_traverse( root, PREORDER );/* displays PREORDER */
	     printf("Inorder:\n");
            tree_traverse( root, INORDER );/* displays INORDER */
            printf("Postorder:\n");
            tree_traverse( root, POSTORDER );/* displays POSTORDER */
	    tree_destroy(root);
            return EXIT_SUCCESS;
        }
        else{
            error("error: must be greater than 0\n");
            return EXIT_FAILURE;
        }
    }
    else{
        usage("usage: treetest #\n");
        return EXIT_FAILURE;
    }
    
}

