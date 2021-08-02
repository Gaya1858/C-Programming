/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
/// contributing author name : Gayathri kanagaraj
///  datd 09/08/2020
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own. You should make the formatting consistent.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///

#include <stdio.h>
#include <stdlib.h>
/*
 *header() just displays welcome message*
 *
 */
void header(void)
{
      printf("\n\t..Welcome to the Game of life..\n");
}
/*
 *this function counts the living organism around that living cell
 *@param row - row size
 *@param col - column size
 *@param life - char 2d array
 *@param a - current row 
 *@param b - current col
 *@return numbers organisms aroung the cell int value
 */
int survivalRule(int row,int col,char life[row][col],int a,int b){
    int neighbors = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            int x = (a+i+row) % row;
            int y = (b+j+col) % col;
            if(life[x][y] =='*'){
               neighbors = neighbors+1;
            }
        }
    }
    if(life[a][b] == '*'){
        neighbors = neighbors-1;
        
    }
    return neighbors;
}
/*
 *this function counts the living organism around that dead cell
 *@param row - row size
 *@param col - column size
 *@param life - char 2d array
 *@param a - current row
 *@param b - current col
 *@return numbers organisms aroung the cell int value
 */
int birthRule(int row,int col,char life[row][col],int a, int b){
    int neighbors = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            int x = (a+i+row) % row;
            int y = (b+j+col) % col;
            if(life[x][y] == '*'){
		neighbors = neighbors+1;
            }
        }
    }
    return neighbors;
}
/*
 *this function checks count and use game logic to put value
 *to the living  cell -if neighbors == 3 or 2 then it stays alive
 *@param row - row size
 *@param col - column size
 *@param life - char 2d array
 *@param a - current row
 *@param b - current col
 *@param sum - count of neighbors
 *
 */
void birth(int x,int y,char life[x][y],int a, int b,int sum){
    if(sum ==  2 || sum == 3){
        life[a][b] = '*';
    }
    else{
        life[a][b] = ' ';
    }
}
/*
 *this function checks count and use game logic to put value
 *to the dead cell -if neighbors == 3 then it becomes alive
 *@param row - row size
 *@param col - column size
 *@param life - char 2d array
 *@param a - current row
 *@param b - current col
 *@param sum - count of neighbors
 *
 */
void death(int x,int y,char life[x][y],int a, int b,int sum){
    if(sum == 3){
        life[a][b] = '*';
    }
}
/*
 *this function assigns value tot he birthRul survivalrule,birth and death
 *function. it creates copyof life grid to manage the consistency of
 *modifying cells
 *@param row - row size
 *@param col - column size
 *@param life - char 2d array
 *
 */
void rule(int x,int y,char life[x][y])//fix6: removed unused variables x,y
{
      int row, col;
      int neighbors = 0;
      int neighbors1 = 0;
      char copylife[x][y];
      for(int row = 0; row < x; row++){
        for(int col = 0; col < y; col++){
            copylife[row][col] = life[row][col];
        }
      }
      for(row = 0; row < x; row++)
      {
         for(col = 0; col < y; col++)
	 {   if(copylife[row][col] == '*')
            {
                neighbors = survivalRule(x,y,copylife,row,col);
                birth(x,y,life,row,col,neighbors);
            }
           
	    else  if(copylife[row][col] == ' ')
            {
                 neighbors1 = birthRule(x,y,copylife,row,col);
                 death(x,y,life,row,col,neighbors1);
            }
           
        }
    }
}
      
/*
 * main function creates life gris and assigns initial values
 * to the gird using random value funtion.
 * gets the user input and fills the grid
 * displays final generations of cells
 */
int main(void)
{
      int orgs; /* to store user input*/
      int i=0,row=0, col=0,x=20,y=20; /* variables for whole programs*/
      char life[x][y]; /* grid size*/
      int count = 0;
      header(); 

      printf("\nPlease enter the initial number of organisms: ");
      scanf("%i", &orgs);

      srand( 31 );
     /* changed the for loop to while to correct the input organism*/
      while(i<orgs){
     	row = rand() % x;
        col = rand() % y;
	if(life[row][col] != '*'){
             life[row][col] = '*';//fix2: changed == to =
	     i+=1;
	  }
	
      }
      /* for loop to check grid value and assigns space if it is empty*/
      for(row = 0; row<x; row++)
      {
          for(col = 0; col<y; col++)
          {
              if(life[row][col] != '*')
                  life[row][col] = ' '; //fix2: changed == to =
          }
      }
      printf("\n");
     /* calls rule funstion and display 100 generations*/
      while ( count<100 ) {// output end after 100generations
          
	      for(row = 0; row<x; row++)
              {
              	for(col = 0; col<y; col++)
                {
                  printf("%c", life[row][col]);//fix1: chnage format specifies from %s to %c

               }
               puts(" ");
          }
	  rule(x,y,life);
          printf("\ngeneration: %d\n", count);
          count++;
      }

      return 0;
}

