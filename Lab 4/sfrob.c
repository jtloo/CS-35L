#include <stdio.h>
#include<stdlib.h>

int frobcmp(const void *a, const void *b)
{
    
  const char *word1 = *(const char**)a;
  const char *word2 = *(const char**)b;
    
  int cmpResult;
  while(1)
    {
      if (*word1 == ' ' && *word2 == ' ') //The words are the same
        {
	  cmpResult = 0;
	  break;
        }
      else if (*word1 == ' ' && *word2 != ' ') //a is shorter than b, so a > b
        {
	  cmpResult = 1;
	  break;
        }
      else if (*word1 != ' ' && *word2 == ' ') //a is longer than b, so a < b
        {
	  cmpResult = -1;
	  break;
        }
      else if (((*word1)^42) > ((*word2)^42)) //Unfrobnicated a > unfrobnicated b
        {
	  cmpResult = 1;
	  break;
        }
      else if (((*word1)^42) < ((*word2)^42)) //Unfrobnicated a < unfrobnicated b
        {
	  cmpResult = -1;
	  break;
        }
      word1++;
      word2++;
    }
  return cmpResult;
}

void errorMessage(int code) //Easy function call for Error
{
  switch (code)
    {
    case 1: //Error Allocating Memory
      fprintf(stderr, "Error: Can't Allocate Memory");
      break;
    case 2: //Error stdin
      fprintf(stdout, "Error: Can't Read Input");
      break;
    default:
      break;
    }
  exit(1);
}


int main(int argc, const char * argv[]) {
  char *readWord = malloc(sizeof(char));
  int readWordpos = 0;
  char **array = malloc(sizeof(char*));
  int arraypos = 0;
  int numElements = 0;
    
  if (readWord == NULL || array == NULL)
    {
      errorMessage(1); //Error Allocating Memory
    }
  char tempWord = ' ';
  while(1)
    {
      tempWord = getchar();
      if (ferror(stdin)) //Can't read the input
        {
	  errorMessage(2); //Error stdin
        }
        
      if (tempWord == EOF) //End of the string input
        {
	  if (readWordpos != 0) //There is no space at the end of input
            {
	      tempWord = ' '; //Add in the space to the word
	      char* tempReadWord = realloc(readWord, (readWordpos+1)*sizeof(char));
	      readWord = tempReadWord;
	      if (readWord == NULL)
                {
		  errorMessage(1);
                }
	      readWord[readWordpos] = tempWord;
	      readWordpos++;
                
	      char** temparray = realloc(array, (arraypos+1)*sizeof(char*));
	      array = temparray;
	      array[arraypos] = readWord;
	      arraypos++;
	      numElements++;
                
	      if (array == NULL)
                {
		  errorMessage(1); //Error Allocating Memory
                }

            }
	  break;
        }
        
      if (tempWord == ' ' && readWordpos != 0) //Reached the end of a word
        {
	  char* tempReadWord = realloc(readWord, (readWordpos+1)*sizeof(char)); //Adding the Space
	  readWord = tempReadWord;
	  if (readWord == NULL)
            {
	      errorMessage(1); //Error Allocating Memory
            }
	  readWord[readWordpos] = tempWord;
	  readWordpos++;
            
	  char** temparray = realloc(array, (arraypos+1)*sizeof(char*));
	  array = temparray;
	  array[arraypos] = readWord;
	  arraypos++;
	  numElements++;
            
	  if (array == NULL)
            {
	      errorMessage(1); //Error Allocating Memory
            }
            
	  readWord = NULL; //Reset the read in words to read new words
	  readWord = malloc(sizeof(char));
	  readWordpos = 0;
            
	  if (readWord == NULL)
            {
	      errorMessage(1); //Error Allocating Memory
            }
            
	  continue;
        }
        
      char* tempReadWord = realloc(readWord, (readWordpos+1)*sizeof(char)); //Default: add letter to current word
      readWord = tempReadWord;
      if (readWord == NULL)
        {
	  errorMessage(1); //Error Allocating Memory
        }
      readWord[readWordpos] = tempWord;
      readWordpos++;
        
    }
    
    
  qsort(array, (numElements), sizeof(char*), frobcmp); //Sort the inputted words
    
  int x;
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
  exit(0);
    
}
