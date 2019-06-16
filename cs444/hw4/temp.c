#include <stdio.h>
#include <stdlib.h>

int main(void){
   int num1 = 60, num2 = 80;
   int print_num = ((100 * num1) + (num2 / 2))/num2;
   printf("print_num = %d\n", print_num);
   return print_num;
}
