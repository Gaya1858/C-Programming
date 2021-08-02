///
/// CS243 Project1
/// Lexical Analysis
/// Author Gayathri Kanagaraj
/// Dated 09/27/2020
///scanner.c 
///
#include "scanner.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * classify function returns int class Define macro from Classes.h
 * @param c - it takes chararater as input
 * @return int - returns classes define macro
 */
int classify(char c){
    int y =c;
    int charClass =0;
    if(c ==' '||c =='\n'||c=='\t'){
        charClass =CC_WS;
    }
    else if(isalpha(c)|| c =='_' ){
        charClass =CC_ALPHA;
    }
    else if(isdigit(c)){
        if(c=='0'){
            charClass =CC_ZERO;
        }
        else if(c =='8'|| c =='9'){
            charClass =CC_DECIMAL;
        }
        else{
            charClass =CC_OCTAL;
        }
    }

    else if(c =='/'){
        charClass =CC_SLASH;
    }
    else if(c =='*'){
        charClass =CC_STAR;
    }
    else if(c =='+'||c =='-'||c=='%'){
        charClass =CC_ARITH;
    }
    else if((y>(0) && y<=8)||(y >=11 && y<=31)||(y >=33 && y<=36)||
       (y >=38 && y<=41)|| y == 44|| y==46||(y >=58 && y<=64)
       ||(y >=91 && y<=94)|| y ==96 ||(y >=123 && y<=127)){
        charClass = CC_OTHER;
    }
    else if(y<=0 || c == EOF|| c==0){
        charClass =CC_EOF;
    }
    else{
        charClass=CC_ERROR;
    }
    return charClass;
}
/*
 * displayState function, loops through FSM and displayes the output
 * @param start - int start stae value
 * @param accpet - accept state value
 * @param size - size of the array
 * @param input - input array
 * @param row - row of the struct
 * @param col - col of the struct
 * @param tm - 2d struct for transition matrix
 */
void displayState(int start,int accept,int size,char input[size],int col,struct TransMatrix tm[][col]){
    int i =0;
    int current = start;
    int class;
    char buffer[80];
    int b =0;
    while (i<size){
        class =classify(input[i]);
        printf("%d ",current);
	if((class == CC_ERROR)|| current ==99){
            printf("rejected\n");
	    int x =i;
            while( x<size && input[x]!=' '){
	    	x++;
	    }
	    i=x;
	    b=0;
        }
        if(tm[current][class].cell[1] =='s'){
            buffer[b]=input[i];  
            b++;
         }
	 current = atoi(&tm[current][class].cell[0]);
         if((class == CC_WS && current == accept)){  
	    buffer[b] ='\0';
	    printf("%d recognized ",accept); 
	    printf("'%s'\n",buffer);
            current = start;
            b=0;
	   
        }
	if(class == CC_EOF|| i ==size-1){
	    printf("%d EOF\n", accept);
	    break; 
	}
        i++;
    }
}

