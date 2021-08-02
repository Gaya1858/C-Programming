/// quicksort.c 
///Uses Function:quicksort(1,2) 
///the quicksort algorithm to sort values and return a pointer to an array
/// Function:quicksort_threaded(1)
/// this function returns a sorted array pointer using thread
/// Auhor Gayathri Kanagaraj 
/// Date 11/13/2020
///
#include <stdio.h>
#include <pthread.h>
#include <getopt.h>
#include <string.h>
#include<stdio.h>

/// function int *quicksort( size_t size, const int *data )
///Uses the quicksort algorithm above to sort the provided array of data. data is an 
///array of int containing size number of values. It sorts without threading. It returns///a pointer to an array of sorted int. The function must not modify the original array.///@param size - size_t number of elements in the int array
///@param data - int pointer 
///@return *int - int pointer of the sorted int array

int *quicksort( size_t size, const int *data ){
	int * qsort =NULL;
	return qsort;
}
///function void *quicksort_threaded( void *args )
///Uses the quicksort algorithm modified to be threaded. Each recursive call to
///quicksort_threaded runs as a thread. The args will be a data structure of your 
///choice, but it must include the information required to perform the sort: a array of
///int and the size. (This is similar to the information required by the non-threaded 
///version.) It returns a pointer to an array of sorted int cast to a void *. The function 
///@param data - void pointer for the int array
//@return *void - sorted int values as an void pointer
void *quicksort_threaded( void *args ){
	void *qsort =NULL;
	return qsort;
}

/// main.c called ./quicksort [-p] file_of_integers
/// -p is an optional flag to print out the unsorted value 
///Read the file, and print the unsorted value if -p given 
/// print out the sorted value which uses quicksort() function
///also print out the quicksort_threaded() function
//@param argc -int value,will be the number of strings pointed to by argv
//@param argv - character array of arguments.
///@return int - 0 on success anything else on failure.
int main(int argc, const char * argv[]) {
	if(argc>0){
		int opt = 0;
		int print =0;
		char  *filename =NULL;
		while((opt =getopt(argc,argv,"p"))!=-1){
			switch(opt){
				case 'p':
					print =1;
					break;
			}
		}
		for(; optind<argc; optind++){
			filename =malloc(sizeof(char)*strlen(argv[optind]+1);
			strcpy(filename,argv[optind]);
		}

	return EXIT_SUCCESS;
	}
	else{
		fprintf(stderr,"Error: missing argument.\n"
				"./quicksort [-p] file_of_integers\n");
		return EXIT_FAILURE;
	}
    
}
 
