///
/// CS243 Project1
/// Lexical Analysis
/// Author Gayathri Kanagaraj
/// Dated 09/27/2020
///scanner.h   header file class
///
#include "matrix.h"
#include "classes.h"
#ifndef scanner_h
#define scanner_h
/*
 * classify function returns int class Define macro from Classes.h
 * @param c - it takes chararater as input
 * @return int - returns classes define macro 
 */
int classify(char c);
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
void displayState(int start,int accept,int size,char input[size],int col,struct TransMatrix tm[][col]);
#endif /* scanner_h */
