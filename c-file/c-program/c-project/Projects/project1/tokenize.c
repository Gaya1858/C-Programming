///
/// CS243 Project1
/// Lexical Analysis
/// Author Gayathri Kanagaraj
/// Dated 09/27/2020
///tokenize.c   is driver class. it reads command line arguments and allocate the values to the function that reads tm.1 file and input strings.
///

#include "scanner.h"
#include <stdio.h>
#include "classes.h"
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int BUFLENGTH =128; /// for number of characters in a line
int TOKENSIZE =80; ///for length of a token

/// output a usage message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void usage( char message[]) {
    fprintf( stderr, "%s", message );
}
/*
 *main function reads command line arguements
 *1. reads file name and if its empty ends program with EXIT_FAILURE message
 *2. else it converts file to the 2d array of struct using function from matrix.c
 *@param argc - number of elements from command line
 *@param argv - character array for the commandline elements
 */
int main(int argc, const char * argv[]) {
    /*if statement checks whether argc is greater than 1 or not
     *if less than one return stderr usage
     */
    if( argc > 1){
        FILE *fp;
        fp = fopen(argv[1],"r");
        int count =0;
        int numOfState =0;
        int column =11;
        char readlines[75][128];
        if(fp !=NULL){/* this checks whether the file is null or not if null returns            Perror message*/
            char *ptr, buf[BUFLENGTH];
            while((ptr=fgets(buf,BUFLENGTH,fp))){
                strcpy(readlines[count],buf);
                count++;
            }
        }
        else{
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
        char *p;
        p=strchr(readlines[0],' ');
        numOfState =atoi(p); /// number states value
   

        struct TransMatrix tm[numOfState][column]; ///struct initialization

        int start=0; ///start state value
        int accept =0;///accept state value
        int rowNum=0;/// rowNum copied from the file
        for(int  i=1; i<count;i++){
            if(i==1){/* it sets up start state*/
                p=strchr(readlines[i],' ');
                start=atoi(p);


            }
            else if(i==2){/* it sets up accept state*/
                p=strchr(readlines[i],' ');
                accept=atoi(p);
                createTm(numOfState, column, tm);/* initializes values 99d to the struct*/

            }
            /* else passes lines from file, struct to the function updateTm to update the struct*/
            else{
               rowNum=atoi(&readlines[i][0]);
                updateTm(readlines[i],column,rowNum,tm);


            }
        }
        fclose(fp);/* to close file*/
        int inputCharSize = numOfState * TOKENSIZE;/* number of inout character*/
        char inputArr[inputCharSize];	/* char array to store input characters */
	char c;
	int a =0;
	c =getchar();/* to read user std input character*/
	/* while loop runs through until it sees EOF character and stores the input value into         an array - inputArr */
	while(c!= EOF){
	   inputArr[a] =c;
	   c=getchar();
	   a++;
	}
	int value = a+1;
        char arr[value];
        for(int j =0;j<value; j++){
            arr[j]= inputArr[j];
        }
	printf("Scanning using the following matrix: \n");
        display(numOfState, column, tm);/*to display matrix*/
	displayState(start,accept,value,arr,column,tm);/* display the finitestate output*/
        return (0);      
    }
    else{
        usage("usage: ./tokenize tmfile\n");
        return EXIT_FAILURE;
    }
}

