///
/// CS243 Project1
/// Lexical Analysis
/// Author Gayathri Kanagaraj
/// Dated 09/27/2020
///tmatrix.h   header file class
///

#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * createTm function initializes the value "99d" and "0d for the accepting state
 * @param accept- accepting state value
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void createTm(int x, int y,struct TransMatrix tm[][y]){
    for(int i =0;i<x;i++){
       for(int j=0; j<y; j++){            
          strcpy(tm[i][j].cell,"99d");
       }      
    }    
}
/*
 * display function displays the 2d array of struct
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void display(int x, int y, struct TransMatrix tm[][y]){
    for(int i =0;i<y;i++){
        printf("\t%d",i);	
    }
    printf("\n");
    for(int i =0;i<x;i++){
        printf("%d\t",i);
       for(int j=0; j<y; j++){
            printf("%s\t",tm[i][j].cell);
        }  
	printf("\n");
    }
}
/*
 * UpdateTm function reads lines and stores value to the 2d array of struct
 * @param *buf - pointer for the charater array
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void updateTm(char *buf, int y,int row1, struct TransMatrix tm[][y]){
    char *p;
    p = strtok(buf," \n");
  
    int row =row1;
    while(p!= NULL){
        if(strlen(p)>1){
            int n =atoi(&p[0]);
            strcpy(tm[row][n].cell, &p[strlen(p)-2]);
        }
        
        p =strtok(NULL," \n");
    }   
    
}

