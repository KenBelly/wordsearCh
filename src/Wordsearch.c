/* CPRE 186: Wordsearch Project
 *
 * Author: Ben Kelly (GitHub/KenBelly)
 * Date: Sept. 20, 2022  
 *
 * To compile: navigate to src directory and type "make"
 *
 * For usage: after compiling, navigate to src directory and type: 
 * ./wordsearch [input file] [puzzle dimensions]
 */

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

//Defines
#define BLANK ' '
#define DEBUG true
#define MAXPUZZLESIZE 60
#define MAXWORDS 50


//Global Declarations
char PUZZLE[MAXPUZZLESIZE][MAXPUZZLESIZE];

//Function Declarations
void printPuzzle(int size_x, int size_y);
void initPuzzle(int size_x, int size_y);
void fillPuzzle(int size_x, int size_y);

//Main Function
int main(int argc, char* argv[])
{
  //First n Foremost: Check arguments
  if(argc != 4){
	fprintf(stderr, "\nError: Incorrect number of arguments! Expected 3 arguments, recieved: [%d]", argc - 1);
	fprintf(stderr, "\n\nUsage: ./wordsearch [input file] [puzzle dimensions]\n");
    return 1;
  }

  for(int i = 0; )

  int wordCount, puzzleSize_X, puzzleSize_Y;
  char* wordlist[MAXWORDS];

  

  return 0;
}

/* Helper function: printPuzzle
 * Params: Dimensions of puzzle
 * Returns: Prints the puzzle's current state to screen
 */
void printPuzzle(int size_x, int size_y)
{
  for(int i = 0; i < size_y; i++)
  {
    for(int j = 0; j < size_x; j++)
    {
      printf("%c ", PUZZLE[j][i]);
    }
    printf("\n");
  }
}

/* Helper function: initPuzzle
 * Parameters: size of puzzle (x & y)
 * Returns: Puzzle filled with blanks
 * This function will fill the puzzle with blanks regardless of what's already set 
 */
void initPuzzle(int size_x, int size_y)
{
  for(int i = 0; i < size_y; i++)
  {
    for(int j = 0; j < size_x; j++)
    {
      PUZZLE[j][i] = BLANK;
    }
  }
}

/* Helper function: fillPuzzle
 * Parameters: size of puzzle (x & y)
 * Returns: Puzzle filled with random letters
 * This function will ignore any spaces that already have letters in them
 */
void fillPuzzle(int size_x, int size_y)
{
  char c;
  for(int i = 0; i < size_y; i++)
  {
    for(int j = 0; j < size_x; j++)
    {
      if(PUZZLE[j][i] == BLANK)
      {
        c = 'A' + (rand()%26);
        PUZZLE[j][i] = c;
      }
    }
  }
}