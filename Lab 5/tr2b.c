#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
  const char *from = argv[1];
  const char *to = argv[2];
    
  int sizeFrom = strlen(from);
  int sizeTo = strlen(to);
    
  if (sizeFrom != sizeTo)
    {
      fprintf(stderr, "Error: From and To are different lengths");
      exit(1);
    }
    
  int i;
  int j;
  for (i = 0; i < sizeFrom; i++)
    {
      for (j = 0; j < sizeFrom; j++)
        {
	  if (i == j)
            {
	      continue;
            }
	  else
            {
	      if (from[i] == from[j])
                {
		  fprintf(stderr, "Error: from has duplicate bits");
		  exit(1);
                }
            }
        }
    }
  int readChar;
  int x;
  while (1)
    {
      readChar = getchar();
      if (ferror(stdin))
        {
	  fprintf(stderr, "Error: Could not read input");
	  exit(1);
        }
        
      if (readChar == EOF)
        {
	  break;
        }
        
      for(x=0; x < sizeFrom; x++)
        {
	  if (readChar == from[x])
            {
	      readChar = to[x];
	      break;
            }
        }
        
      putchar(readChar);
    }
}
