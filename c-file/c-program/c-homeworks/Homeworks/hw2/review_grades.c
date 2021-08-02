///
/// File: review_grades.h
/// review_grades.h is the interface for function function converts a C string to an integer value
///  main function that display the output of mean, standard deviation of given scores
///  it uses different functions
///  str_to_int() - converts string to int
///  mean() - returns avearge of the scores
///  std_dev() - returns standard deviation of the scores
///  histogram() - prints out the table of grade and number of grades
/// @author csci243: Mechanics Course Account
/// @author gk4045 Gayathri Kanagaraj
/// @date 08/28/2020
///
#include <stdlib.h>
#include <stdio.h>
#include "stats.h"
#include <ctype.h>



/// function convertes string to int alos omits negative values and non numeric values
///@param str  character array
///@return  int value

int str_to_int(char str[]){
    int score =0;
    for (int i =0; str[i]>='0'; ++i){
        if(isdigit(str[i])){
            score = score*10 + str[i] -'0';
        }
        else{
            break;
        }
    }
    
    return score;
}
// output a usage message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void usage( char message[]) {
    fprintf( stderr, "%s", message );
}
/// output a note message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print
void note( char message[] ) {
    fprintf( stderr, "%s", message );
}


///  main function that display the output of mean, standard deviation of given scores
///  it uses different functions
///  str_to_int() - converts string to int
///  mean() - returns avearge of the scores
///  std_dev() - returns standard deviation of the scores
///  histogram() - prints out the table of grade and number of grades
///@param argc - gives int value of commandline argument elements
///@param argv - character array storys command line arguments
///@return -  EXIT_SUCCESS for successful compliation and EXIT-FAILURE for no arguments in commandline

int main(int argc, char * argv[]) {
   
    int count =0;
    
    if(argc>1){
        printf("input population: %d \n",argc-1);
        for(int i =1; i<argc;i++){
            if(isdigit(argv[i][0])){
                count+=1;
            }
        }
        
        int scores[count];
        int x =0;
        for(int j =1; j<argc;j++){
            if(isdigit(argv[j][0])){
                scores[x] =str_to_int(argv[j]);
                printf("%d ",scores[x]);
                x+=1;
            }
            
        }
        printf("\n");
        printf("adjusted population: %d \n",count);
        double mean = average(count, scores);
        printf("mean: %f \n",mean);
        double std = std_dev(count, scores, mean);
        printf("std deviation:%f \n",std);
        histogram(count, scores);
        return  EXIT_SUCCESS;
    }
    
    else{
        usage("usage: review_grades score1 [score2...]\n");
        note("note: ignores negative score values.\n");
        return EXIT_FAILURE;
    }
   
    
}





