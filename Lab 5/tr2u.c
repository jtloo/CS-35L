#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
 
  int sizeArray = 1;
  char readChar[1];
  //readChar[0] = '1';
  ssize_t shouldContinue;
    
  int x;
  while (1)
    {
      shouldContinue = read(0, readChar, 1);
        
      if (shouldContinue == 0 )//0 = read has EOF
        {
	  break;
        }
        
      if (shouldContinue == -1) //-1 = error reading input
        {
	  fprintf(stderr, "Error: Can't read input");
	  exit(1);
        }
        
      for (x = 0; x < sizeFrom; x++)
        {
	  if (readChar[0] == from[x])
            {
	      readChar[0] = to[x];
	      break;
            }
        }
        
      write(1,readChar,1);
    }
}
