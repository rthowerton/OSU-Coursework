 #include <stdio.h>
#include<iostream>
#include <string.h>
#include <algorithm>
using namespace std;

//bool determine_palindrome(char []);
bool check_letters(char[], char[]);
void get_search_replace_strings(/*char [], char [], char[]*/);
void search_replace(char [], char[], char[]);

int main(){
   int choice;
   cout<<"Which function do you want? 1 = palindrome checker, 2 = string replacer: "<<endl;
   cin>>choice;
   //if(choice == 1)
     // determine_palindrome();
   if(choice == 2)
      get_search_replace_strings();
   return 0;
}

/*bool determine_palindrome(char str[]){
   bool palindrome;
   //string mainString, bonusString;
  
   cout<<"Enter a string: "<<endl;
   cin.ignore();
   cin.clear();
   getline(cin, mainString);
   bonusString = mainString;
   reverse(mainString.begin(), mainString.end());
   palindrome = check_letters(mainString, bonusString);
   if(palindrome == true)
      cout<<"Is a palindrome."<<endl;
   else
      cout<<"Not a palindrome."<<endl;
   return palindrome;
}*/
/*
bool determine_palindrome(char str[]){
	
   	//char str2[256] = str;

	char str2 [256] = reverse(str, strlen(str));

	if(strcmp(str, str2)==0)
	{ cout << "String is palindrome" << endl;
	   return true;
	}
	else
	{
	   cout << "String isn't palindrome" << endl;
	   return false;
	}
	
*/

  
/*bool check_letters(string str1, string str2){
   bool check;
   for(int i = 0; i < str2.length(); i++){
      if(str1.at(i) != str2.at(i))
	 check = false;
      else
	 check = true;
   }
   return check;
}*/

void get_search_replace_strings(){
   cin.ignore();
   cin.clear();
   char mainString[256], search[256], replacement[256];
   cout<<"Enter a string: "<<endl;
   cin.getline(mainString, 256, '\n');
   cout<<"Enter a string to search: "<<endl;
   cin.getline(search, 256, '\n');
   cout<<"Enter a string to do the replacing: "<<endl;
   cin.getline(replacement, 256, '\n');
   search_replace(mainString, search, replacement);
}

void search_replace(char str1[], char str2[], char str3[]){
   /*int count = 0;
   size_t pos = 0;
   while((pos = str1.find(str2, pos)) != string::npos){
      str1.replace(pos, str2.length(), str3);
      count++;
      pos += str3.length();
   }*/
   char * pch;
   pch = strstr(str1, str2);
   strncpy(pch, str3, strlen(str3));
   puts(str1); 
   cout<<"New string: "<<str1<<endl;
   //cout<<"Number of replacements: "<<count<<endl;
}






