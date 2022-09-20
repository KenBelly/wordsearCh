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
#define DEBUG true

//Global Declarations


//Function Declarations


//Main Function
int main(int argc, char* argv[])
{
  //First n Foremost: Check arguments
  if(argc != 4){
	fprintf(stderr, "\nError: Incorrect number of arguments! Expected 3 arguments, recieved: [%d]", argc - 1);
	fprintf(stderr, "\n\nUsage: ./collatz [starting number]\n");
    return 1;
  }

  

  return 0;
}

