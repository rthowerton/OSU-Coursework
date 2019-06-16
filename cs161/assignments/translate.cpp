/*
 * Program: translate.cpp
 * Author: Ryan Howerton
 * Date: 2/28/2016
 * Description: Translates a c-style string to/from morse code from/to english characters
 * Input: N/A
 * Output: N/A
 */
#include <iostream>
using namespace std;

char* getInput(char* input, int& size);
void toMorse(char* input, int size);
void toEnglish(char* input, int size);
int length(char array[]);

/*
 * Function: int main()
 * Description: Calls getInput() to fill the array of chars to translate.
 * Parameters: N/A
 * Pre-Conditions: N/A
 * Post-Conditions: N/A
 */
int main(){
   int size = 0, choice;
   cout<<"Translate english to morse (1) or\nTranslate morse to english (2):"<<endl;
   cin>>choice;
   cin.ignore();
   cin.clear();
   char* input;
   if(choice == 1){
      cout<<"Enter English Message:"<<endl;
      input  = getInput(input, size);
      toMorse(input, size);
   }
   else{
      cout<<"Enter Morse Message:"<<endl;
      input = getInput(input, size);
      toEnglish(input, size);
   }
   return 0;
}

/*
 * Function: char* getInput()
 * Description: Fills an empty string with either english or morse chars.
 * Parameters: char* input, int& size
 * Pre-Conditions: input is empty, size == 0.
 * Post-Conditions: input is full of chars, size == length of input.
 */
char* getInput(char* input, int& size){
   char temp;
   while(cin.get(temp) && temp !='\n'){
	 size++;
	 char* hold = new char[size];
	 for(int i = 0; i < size-1; i++){
	    hold[i] = input[i];
	 }
	 hold[size-1] = temp;
	 delete[] input;
	 input = hold;
   }
   size += 3;
   char* hold = new char[size];
   for(int i = 0; i < size-3; i++)
      hold[i] = input[i];
   delete[] input;
   for(int i = size-3; i < size; i++)
      hold[i] = ' ';
   input = hold;
   return input;
}

/*
 * Function: void toMorse()
 * Description: Translates the english user input to morse code.
 * Parameters: char* input, int size
 * Pre-Conditions: input is full of english chars, size == length of input.
 * Post-Conditions: prints out translation of enlgish with proper spacing.
 */
void toMorse(char* input, int size){
   char abc[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
   char morse[27][9] = {{".-   \0"},{"-...   \0"},{"-.-.   \0"},{"-..   \0"},{".   \0"},{"..-.   \0"},{"--.   \0"},{"....   \0"},{"..   \0"},{".---   \0"},{"-.-   \0"},{".-..   \0"},{"--   \0"},{"-.   \0"},{"---   \0"},{".--.   \0"},{"--.-   \0"},{".-.   \0"},{"...   \0"},{"-   \0"},{"..-   \0"},{"...-   \0"},{".--   \0"},{"-..-   \0"},{"-.--   \0"},{"--..   \0"},{"       \0"}};
   for(int i = 0; i < size; i++){
      if(input[i] == ' ')
	 cout<<morse[26];
      else
         for(int j = 0; j < 26; j++){
	    if(input[i] == abc[j])
	       cout<<morse[j];
         }
   }
   cout<<endl;
}

/*
 * Function: void toEnglish
 * Description: Translates the morse user input to english chars.
 * Parameters: char* input, int size
 * Pre-Conditions: input is full of properly spaced morse, size == length of input.
 * Post-Conditions: prints out translation of morse with proper spacing.
 */
void toEnglish(char* input, int size){
   char abc[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
   char morse[27][9] = {{".-   \0"},{"-...   \0"},{"-.-.   \0"},{"-..   \0"},{".   \0"},{"..-.   \0"},{"--.   \0"},{"....   \0"},{"..   \0"},{".---   \0"},{"-.-   \0"},{".-..   \0"},{"--   \0"},{"-.   \0"},{"---   \0"},{".--.   \0"},{"--.-   \0"},{".-.   \0"},{"...   \0"},{"-   \0"},{"..-   \0"},{"...-   \0"},{".--   \0"},{"-..-   \0"},{"-.--   \0"},{"--..   \0"},{"       \0"}};
   int count = 0;
   for(int i = 0; i < size;){
      for(int j = 0; j < 27; j++){
         for(int k = 0; k < length(morse[j]); k++){
	    if(input[i+k] == morse[j][k])
	       count++;
	    else{
	       count = 0;
	       break;
	    }
	    if(count == length(morse[j])){
	       cout<<abc[j];
	       count = 0;
	       j = 27;
	       i += k+1;
	    }
         } 
      }
   }
   cout<<endl;
}

/*
 * Function: int length
 * Description: Performs same function as strlen from string.h.
 * Parameters: char array[]
 * Pre-Conditions: array is filled with chars.
 * Post-Conditions: returns length of array equal to non-NULL chars.
 */
int length(char array[]){
   char x = array[0];
   int num = 0;
   for(num; x != '\0'; num++){
      x = array[num];
   }
   return num-1;
}
