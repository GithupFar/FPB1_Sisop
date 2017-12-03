#include <stdio.h>
#include <stdlib.h> //atol
#include <string.h> //strcpy

int main (int argc, char * argv [])
{
  long int number,div=2,i=1;
  char buffer[256];
  strcpy (buffer,argv[i]);
  number = atol(buffer);
  printf("%s: ",buffer);
  
   while(number!=0){
        if(number%div!=0)
            div = div + 1;
        else {
            number = number / div;
            printf("%ld ",div);
            if(number==1)
                break;
        }
    }
  printf("\n");  

  return 0;
}
