/* C implementation QuickSort */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
  
// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
int *quickSort(int arr[], int low, int high) 
{	
    int*poin = malloc(sizeof(int)*high+1);
	static int pio =0;    
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
 	          at right place */
    	int pi =partition(arr, low, high);
        poin[pio] =arr[pi];
       	pio++;	
	
	printf("Partioning index:[%d]\n",pi);  
        // Separately sort elements before 
        // partition and after partition 
        
	quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
    return poin;
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int arr[] = {10, 7, 8, 9, 1, 5}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    int * qsort = quickSort(arr, 0, n-1); 
    printf("Sorted array: \n"); 
    printArray(qsort, n); 
    return 0; 
} 
