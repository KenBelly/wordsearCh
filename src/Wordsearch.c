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
#define MAXPUZZLESIZE 64
#define MAXWORDS 32
#define WORDLENGTH 16


//Global Declarations
char PUZZLE[MAXPUZZLESIZE][MAXPUZZLESIZE];

//Function Declarations
void initPuzzle(int size_x, int size_y);
void printPuzzle(int size_x, int size_y);
void fillPuzzle(int size_x, int size_y);
int readWords(char *wordList[MAXWORDS], char *inputFile);
void trimws(char *s);

//Main Function
int main(int argc, char *argv[])
{
  //First n Foremost: Check arguments
  if(argc != 4){
	fprintf(stderr, "\nError: Incorrect number of arguments! Expected 3 arguments, recieved: [%d]", argc - 1);
	fprintf(stderr, "\n\nUsage: ./wordsearch [input file] [puzzle dimensions]\n");
    return 1;
  }

  if(DEBUG)//DEBUG: Check that words were read correctly
  {

  }

  int wordCount, puzzleSize_X, puzzleSize_Y;
  char *wordlist[MAXWORDS];

  

  return 0;
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

/* Helper function: readWords
 * Parameters: An array of strings to store the words into and a string for the input file
 * Returns: The number of words read from the input file & the list of words into the array
 * This function will read words from a given input file (separating words by newlines)
 *      and will create a data structure to store all of these words
 */
int readWords(char *wordList[MAXWORDS], char *inputFile)
{
  int wordCount = 0;
  char word[WORDLENGTH];
  char *line;
  FILE *f;

  //Open the file for "r"eading
  f = fopen(inputFile, "r"); 

  //Save each line as a single word with whitespace removed into our word list 
  while(feof(f) == 0)
  {
    line = fgets(word, WORDLENGTH, f);

    if(line != NULL)
    {
      trimws(word);
      wordList[wordCount] = (char *)malloc(strlen(word) + 1);
      strcpy(wordList[wordCount], word);
      wordCount++;
    }
  }

  //Close the file
  fclose(f);

  return wordCount;
}

/* Helper function: trimws
 * Parameters: String with whitespace to be removed
 * Returns: String without whitespace
 * This function removes whitespace from words (``\t''``\n''``\v''``\f''``\r''`` '')
 */
void trimws(char *s)
{
  int length = strlen(s);

  //If given an empty string, exit 
  if(length == 0) 
    return;

  int x = length - 1;

  while(isspace(s[x]) && (x >= 0))
  {
    s[x] = '\0';
    x--;
  }
}