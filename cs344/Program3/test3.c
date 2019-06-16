#include <stdio.h>
#include <string.h>

int main(){
   char str[] = "This is a $$ string";
   char* pch;
   pch = strstr(str,"$$");
   //sprintf(pch, "%d", getpid());
   strncpy(pch, "sample", 6);
   puts(str);
   return 0;
}
