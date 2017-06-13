//
//  sfrobu.c
//  Lab 5 tr2b
//
//  Created by Justin Loo on 5/6/17.
//  Copyright © 2017 Justin Loo. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int fFlag;

int frobcmp(const void *a, const void *b)
{
    
  const char *word1 = *(const char**)a;
  const char *word2 = *(const char**)b;
    
  int cmpResult;
    
  int i = strlen(word1);
  int j = strlen(word2);
    
  unsigned char uWord1;
  unsigned char uWord2;
  int x = 0;
  int y = 0;
  while(1)
    {
      uWord1 = (unsigned)word1[x];
      uWord2 = (unsigned)word2[y];
        
      if (fFlag == 1)
        {
	  uWord1 = toupper(uWord1);
	  uWord2 = toupper(uWord2);
        }
        
      if (uWord1 == ' ' && uWord2 == ' ') //The words are the same
        {
	  cmpResult = 0;
	  break;
        }
      else if (uWord1 == ' ' && uWord2 != ' ') //a is shorter than b, so a > b
        {
	  cmpResult = 1;
	  break;
        }
      else if (uWord1 != ' ' && uWord2 == ' ') //a is longer than b, so a < b
        {
	  cmpResult = -1;
	  break;
        }
      else if (((uWord1)^42) > ((uWord2)^42)) //Unfrobnicated a > unfrobnicated b
        {
	  cmpResult = 1;
	  break;
        }
      else if (((uWord1)^42) < ((uWord2)^42)) //Unfrobnicated a < unfrobnicated b
        {
	  cmpResult = -1;
	  break;
        }
      x++;
      y++;
    }
  return cmpResult;
}

void errorMessage(int code) //Easy function call for Error
{
  switch (code)
    {
    case 1: //Error incorrect number of arguments
      fprintf(stderr, "Error: Incorrect number of arguments");
      break;
    case 2: //Error non f option passed in
      fprintf(stderr, "Error: Unknown option passed in");
      break;
    case 3: //Error Allocating Memory
      fprintf(stderr, "Error: Can't Allocate Memory");
      break;
    case 4: //Error stdin
      fprintf(stderr, "Error: Can't Read Input");
      break;
    case 5:
      fprintf(stderr, "Error: fstat failure");
      break;
    default:
      break;
    }
  exit(1);
}


int main(int argc, const char * argv[]) {
  fFlag = 0;
  int fileSize = 0;
  if (argc > 2)
    {
      errorMessage(1);
    }
    
  if (argc == 2) //There was an option inputted
    {
      const char *optionCheck = argv[1];
      if (strlen(optionCheck) != 2) //The option is not of the format "-f"
        {
	  errorMessage(2);
        }
      if (optionCheck[0] == '-' && optionCheck[1] == 'f') //Sets program to run with fFlag on
        {
	  fFlag = 1;
        }
      else //Option that is not f inputted
        {
	  errorMessage(2);
        }
    }
    
  struct stat fileToRead;
  int j = fstat(0, &fileToRead);
  if (j < 0) //Error if fstat returned a negative value
    {
      errorMessage(5);
    }
    
  if (S_ISREG(fileToRead.st_mode))
    {
      fileSize = fileToRead.st_size;
    }
  else
    {
      fileSize = 0;
    }
    
  char *readWord;
  int readWordpos = 0;
  int sizeOfFile = fileSize;
  if (fileSize != 0)
    {
      readWord = malloc(fileSize*sizeof(char));
    }
  else
    {
      readWord = malloc(sizeof(char));
      sizeOfFile = 1;
    }
    
  char **array = malloc(sizeof(char*));
  int arraypos = 0;
  int numElements = 0;
    
  if (readWord == NULL || array == NULL)
    {
      errorMessage(3); //Error Allocating Memory
    }
    
  char tempWord[1];
  int x;
  while(1)
    {
      if (readWordpos >= fileSize)
        {
	  fileSize++;
	  char *tempReadWord = realloc(readWord, fileSize*sizeof(char));
	  readWord = tempReadWord;
	  if (readWord == NULL)
            {
	      errorMessage(3);
            }
        }
        
      x = read(0, tempWord, 1);
      if (x == -1) //Can't read the input
        {
	  errorMessage(4); //Error stdin
        }
        
      if (x == 0) //End of the input
        {
	  if (readWord[readWordpos-1] != ' ') //There is no space at the end of input
            {
	      tempWord[0] = ' '; //Add in the space to the word
	      readWord[readWordpos] = tempWord[0];
	      readWordpos++;
            }
	  break;
        }
        
      if (tempWord[0] == ' ' && readWordpos == 0) //Leading space should be ignored
        {
	  continue;
        }
        
      if (tempWord[0] == ' ' && readWord[readWordpos-1] == ' ') //Consecutive spaces
        {
	  continue;
        }
        
      readWord[readWordpos] = tempWord[0]; //Default: add letter to current word
      readWordpos++;
        
    }
    
  char *pass = malloc(sizeof(char));
  int passPos = 0;
  if (pass == NULL)
    {
      errorMessage(3);
    }
    
  for (x = 0; x < readWordpos; x++)
    {
      char *tempPass = realloc(pass, (passPos+1)*sizeof(char));
      pass = tempPass;
      if (pass == NULL)
        {
	  errorMessage(3);
        }
        
      pass[passPos] = readWord[x];
      passPos++;
        
      if (readWord[x] == ' ')
        {
	  char **tempArray = realloc(array, (arraypos+1)*sizeof(char*));
	  array = tempArray;
	  if (array == NULL)
            {
	      errorMessage(3);
            }

	  array[arraypos] = pass;
	  arraypos++;
	  numElements++;
            
	  pass = NULL;
	  pass = malloc(sizeof(char));
	  passPos = 0;
            
	  if (pass == NULL)
            {
	      errorMessage(3);
            }
	  continue;
        }
    }
    
  qsort(array, numElements, sizeof(char*), frobcmp); //Sort the inputted words
    
  for (x = 0; x < numElements; x++) //Iterate through each word in array
    {
      int y = 0;
      while(1) //Iterate through each character in word
        {
	  char toPrint = array[x][y];
	  if (toPrint == ' ') //Indicates the end of the word
            {
	      break;
            }
	  else
	    putchar(toPrint);
	  y++;
        }
      putchar(' '); //Outputs the ' ' after each word
    }
    
  free(array); //Freeing up the memory used
  free(readWord);
  free(pass);
  exit(0);
}
