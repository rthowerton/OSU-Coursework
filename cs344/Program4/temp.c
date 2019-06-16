#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int mod(int a, int b)
{
       int r = a % b;
       return r < 0 ? r + b : r;
}

int main()
{
   char* msg = "DQNVZ";
   printf("%s\n", msg);
   char* key = "XMCKL";
   printf("%s\n", key);
   char buffer[5];
   int i;
   for(i = 0; i < 5; i++){
      char m, k;
      if(msg[i] == 32) m = 26;
      else m = msg[i] - 65;
      if(key[i] == 32) k = 26;
      else k = key[i] - 65;
      buffer[i] = (char)(mod(m - k, 27)) + 65;
   }
   printf("%s\n", buffer);
}*/

int main(){
   char buffer[512];
   char printer[512];
   FILE* toOpen = fopen("bigFile.txt", "r");
   int i;
   while(fgets(buffer, sizeof(buffer) - 1, toOpen) != NULL){
      memset(printer, '\0', sizeof(printer));
      strcat(printer, buffer);
      printf("%s", printer);
   }
   printf("\n");
   fclose(toOpen);
}
