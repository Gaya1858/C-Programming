///
/// CS243 Project1
/// Lexical Analysis
/// Author Gayathri Kanagaraj
/// Dated 09/27/2020
///tmatrix.h   header file class
///

#ifndef matrix_h
#define matrix_h

/* struct and holds char array of length 4*/
struct TransMatrix{
    char cell[4];
};
/*
 * UpdateTm function reads lines and stores value to the 2d array of struct
 * @param *buf - pointer for the charater array
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void updateTm(char *buf, int y,int row1,struct TransMatrix tm[][y]);
/*
 * display function displays the 2d array of struct
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void display(int x, int y, struct TransMatrix tm[][y]);
/*
 * createTm function initializes the value "99d" and "0d for the accepting state
 * @param accept- accepting state value
 * @param x - row values of the 2d array
 * @param y - column value of the array
 * @param tm - 2d struct to update
 */
void createTm(int x, int y,struct TransMatrix tm[][y]);






#endif /* matrix_h */

