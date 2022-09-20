//CprE 186: Wordsearch
//Needs major re-working to be functioning again
//Author: Ben Kelly (brkelly) (KenBelly)

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


//Defines
#define MAXWORDS 50
#define WORDLEN 13
#define MAXPUZZLESIZE 60
#define EMPTY_SPACE ' '
#define DEBUG 0


//Global Declarations
char PUZZLE[MAXPUZZLESIZE][MAXPUZZLESIZE];


//Function Prototypes
int readWords(char* wl[MAXWORDS], char* filename);
void trimws(char* s);
void fillPuzzleWSpaces(int psX, int psY);
void printPuzzle(int psX, int psY);
int checkFit(int psx, int psy, int lx, int ly, int dir, int len, char* word);
void addWordsToPuzzle(char* wl[MAXWORDS], int puzzleSize_X, int puzzleSize_Y, int numWords);
void fillPuzzle(int psX, int psY);


/* Function name: Main
 * Input: Arguments from user: first the file's name for the word list, then the dimensions of the puzzle
 * Output: Generates a random wordSearch for the user.
 */
int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordCount, puzzleSize_X, puzzleSize_Y;
	wordCount = readWords(wordlist, argv[1]);
	
	if (DEBUG) {//DEBUG: Test if words were read correctly.
		printf("Read %d words from %s \n",wordCount, argv[1]);
		for(int i = 0; i < wordCount; i++){//Prints the list of words following the number of words read.
			printf("%s, ", wordlist[i]);
		}
	}
	
	printf("\n\nPlease enter the dimensions of the puzzle (less than 61(x y)): ");//prompt user
	fflush(stdout);
	scanf("(%d %d)", &puzzleSize_X, &puzzleSize_Y);//Get puzzle size from user
	
	fillPuzzleWSpaces(puzzleSize_X, puzzleSize_Y);//Fills puzzle with spaces (see function)
	
	if (DEBUG){//DEBUG: Print Empty Array
		printPuzzle(puzzleSize_X, puzzleSize_Y);
	}
	
	//Print Key to Puzzle(non filled)
	addWordsToPuzzle(wordlist, puzzleSize_X, puzzleSize_Y, wordCount);
	printPuzzle(puzzleSize_X, puzzleSize_Y);
	
	//Print full puzzle(filled with random letters)
	fillPuzzle(puzzleSize_X, puzzleSize_Y);
	printPuzzle(puzzleSize_X, puzzleSize_Y);
	
	return 0; 
}

/* Function name: readWords
 * Input: Read words from the file and trim any whitespace on them. 
 * Output: The list of words into the array wl, the number of words as a return value.
 */
int readWords(char* wl[MAXWORDS], char* filename){
	int num = 0;
	char word[WORDLEN];
	char *pointer;
	FILE* f;
	f = fopen(filename, "r");
	
	while(feof(f) == 0){
		pointer = fgets(word, WORDLEN, f);
		
		if(pointer != NULL){
			trimws(word);
			wl[num] = (char *)malloc(strlen(word) + 1);
			strcpy(wl[num], word);
			num++;
		}
	}
	
	fclose(f);
	
	return num;
}

/* Function name: trimws
 * Input: A string with whitespace.
 * Output: A string without whitespace.
 */
void trimws(char* s){
	int x, len;
	
	len = strlen(s);
	
	if(len == 0)
		return;
	
	x = len - 1;
	
	while(isspace(s[x]) && (x >= 0)){
		s[x] = '\0';
		x--;
	}
}

/* Function name: fillPuzzleWSpaces
 * Input: Puzzle Array (empty)
 * Output: Puzzle Array filled with Spaces
 */
void fillPuzzleWSpaces(int psX, int psY){
	int i, j;
	for(i = 0; i < psY; i++){
		for(j = 0; j < psX; j++){
			PUZZLE[j][i] = EMPTY_SPACE;
		}
	}
}

/* Function name: printPuzzle
 * Input: Puzzle Array
 * Output: Prints the puzzle to the screen
 */
void printPuzzle(int psX, int psY){
	int i, j;
	for(i = 0; i < psY; i++){
		for(j = 0; j < psX; j++){
			printf("%c ", PUZZLE[j][i]);
		}
		printf("\n");
	}
}

/* Function name: addWordsToPuzzle
 * Input: List of the words, and the user defined size of the puzzle.
 * Implementation: pick random location, and random direction, then loop{ 
 * flip coin->reverse word, check if it fits, if not find new random location & direction.} 
 * Stop after 100 iterations or if fits = true
 * Output: Adds the words to the 2D puzzle array 
 */
void addWordsToPuzzle(char* wl[MAXWORDS], int puzzleSize_X, int puzzleSize_Y, int numWords){
	int i, j = 0, k, l, len, direction, randX, randY, placed = 0;
	char currWord[14];
	
	//Go through and place entire list of words
	for(i = 0; i < numWords; i++){
		//Select next word
		strcpy(currWord, wl[i]);
		
		//Currently broken on Unix systems, looking to reimplement myself once the puzzle is working again
					// //flip coin to reverse word 
					// if((rand()%(2)) == 0){
					// 	strrev(wl[i]); //function in string.h to reverse a word.
					// }
		
		//Set length of word to variable.
		len = strlen(wl[i]);
		
		//Try 100 times to place a word.
		while((j < 100) && placed == 0){
			
			//Choose random direction and location for word to be placed.
			direction = (rand()%4);
			randX = (rand()%(puzzleSize_X + 1));
			randY = (rand()%(puzzleSize_Y + 1));
			
			//Check if the word fits
			if(checkFit(puzzleSize_X, puzzleSize_Y, randX, randY, direction, len, currWord) == 1){
				
				//Place word
				for(k = 0; k < len; k++){
					if(direction == 0){//places upwords (y--)
						PUZZLE[randX][randY] = currWord[k];
						randY = randY - 1;
					}
					if(direction == 1){//places diagonal up (y-- & x++)
						PUZZLE[randX][randY] = currWord[k];
						randY = randY - 1;
						randX = randX + 1;
					}
					if(direction == 2){//places to the right (x++)
						PUZZLE[randX][randY] = currWord[k];
						randX = randX + 1;
					}
					if(direction == 3){//places diagonal down (y++ & x++)
						PUZZLE[randX][randY] = currWord[k];
						randY = randY + 1;
						randX = randX + 1;
					}
				}
				
				//Allows break out of while loop
				placed = 1;
			}
			
			j = j + 1;
		}
		
		//empty current word array before assigning a new word to it
		for(l = 0; l < 14; l++){
			currWord[l] = 0;
		}
		currWord[0] = '\0';
		
		j = 0; //Reset the counter for the while loop.
		placed = 0; //Reset the checker for whether the word was successfully placed or not. 
	}
	
}

/* Function name: checkFit
 * Input: size of wordsearch x & y, location to put word, direction of word, length of word.
 * Output: 1 if it fits, 0 if it goes out of bounds or crosses another word. 
 */
int checkFit(int psx, int psy, int lx, int ly, int dir, int len, char* word){
	//return 1 if word doesn't run into a different character than the one trying to place
	//AND, if the word doesn't run out of bounds. 
	//int i;
	
	//Check if inside bounds
	if((ly + len < psy) && (lx + len < psx)){
		for(int i = 0; i < len; i++){
			//Direction 0 is up. (y--)
			if(dir == 0){
				if(PUZZLE[lx][ly] != ' ' || PUZZLE[lx][ly] == word[i])
					return 0;
				else
					ly = ly - 1;
			}
			//Direction 1 is diagonal up. (y-- & x++)
			if(dir == 1){
				if(PUZZLE[lx][ly] != ' ' || PUZZLE[lx][ly] == word[i])
					return 0;
				else{
					ly = ly - 1;
					lx = lx + 1;
				}
			}
			//Direction 2 is to the right. (x++)
			if(dir == 2){
				if(PUZZLE[lx][ly] != ' ' || PUZZLE[lx][ly] == word[i])
					return 0;
				else
					lx = lx + 1;
			}
			//Direction 3 is diagonal down. (y++ & x++)
			if(dir == 3){
				if(PUZZLE[lx][ly] != ' ' || PUZZLE[lx][ly] == word[i])
					return 0;
				else{
					ly = ly + 1;
					lx = lx + 1;
				}
			}
		}
		return 1;
	}
	return 0;
	
}

/* Function name: fillPuzzle
 * Input: size of puzzle (x&y)
 * Output: Puzzle with empty spaced filled with random characters.
 */
void fillPuzzle(int psX, int psY){
	int i, j;
	char c;
	for(i = 0; i < psY; i++){
		for(j = 0; j < psX; j++){
			if(PUZZLE[j][i] == EMPTY_SPACE){
				c = 'A' + (rand()%26);
				PUZZLE[j][i] = c;
			}
		}
	}
}