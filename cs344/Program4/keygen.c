#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
   if(argc != 2)
   {
      printf("USAGE: %s keyLength\n", argv[0]);
      exit(1);
   }

   srand(time(NULL));

   int for_ctr;
   for(for_ctr = 0; for_ctr < atoi(argv[1]); for_ctr++)
   {
      int ascii_ref = rand() % 27 + 65;
      if(ascii_ref == 91)
	 ascii_ref = 32;
      printf("%c", (char) ascii_ref);
   }
   printf("\n");
   return 0;
}
