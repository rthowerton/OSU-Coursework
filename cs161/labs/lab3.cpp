#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

bool isint(string);

int main()
{
   string cont = "1";
   while(cont == "1")
   {
      string length;
      string letters;
      string upper;
      string lower;
      string numbers;
      string specials;
      double upperPercent = 0;
      double lowerPercent = 0;
      double numPercent = 0;
      double specialPercent = 0;
      double totalPercent = 0;

      srand(time(NULL));

      while(true)
      {
	 cout<<"Password length: ";
         cin>>length;
	 if(isint(length))
	    break;
	 else
	    cout<<"Incorrect value."<<endl;
      }
      cout<<"Do you want letters? 1 = yes, 0 = no: ";
      cin>>letters;
      while(true){
	 for(int i = 0; i < letters.length(); i++){
	    if(!(letters.at(i) >= '0' && letters.at(i) <= '1')){
	       cout<<"Invalid input.\nDo you want letters? 1 = yes, 0 = no: ";
	       cin>>letters;
	       i--;
	    }
	 }
	 break;
      }
      if(letters == "1")
      {
	 cout<<"Do you want upper case? 1 = yes, 0 = no: ";
	 cin>>upper;
         while(true){
	    for(int i = 0; i < upper.length(); i++){
	       if(!(upper.at(i) >= '0' && upper.at(i) <= '1')){
	          cout<<"Invalid input.\nDo you want upper case? 1 = yes, 0 = no: ";
	          cin>>upper;
	          i--;
	    }
	 }
	 break;
      }
	 if(upper == "1")
	 {
	    cout<<"What percentage of the password should be upper case? ";
	    cin>>upperPercent;
	    totalPercent += upperPercent;
	 }
	 cout<<"Do you want lower case? 1 = yes, 0 = no: ";
	 cin>>lower;
         while(true){
	    for(int i = 0; i < lower.length(); i++){
	       if(!(lower.at(i) >= '0' && lower.at(i) <= '1')){
	       cout<<"Invalid input.\nDo you want lower case? 1 = yes, 0 = no: ";
	       cin>>lower;
	       i--;
	    }
	 }
	 break;
      }
	 if(lower == "1")
	 {
	    cout<<"What percentage of the password should be lower case? ";
	    cin>>lowerPercent;
	    totalPercent += lowerPercent;
	 }
      }
      cout<<"Do you want numbers? 1 = yes, 0 = no: ";
      cin>>numbers;
      while(true){
	 for(int i = 0; i < numbers.length(); i++){
	    if(!(numbers.at(i) >= '0' && numbers.at(i) <= '1')){
	       cout<<"Invalid input.\nDo you want numbers? 1 = yes, 0 = no: ";
	       cin>>numbers;
	       i--;
	    }
	 }
	 break;
      }
      if(numbers == "1")
      {
	 cout<<"What percentage of the password should be numbers? ";
	 cin>>numPercent;
	 totalPercent += numPercent;
      }
      cout<<"Do you want special characters? 1 = yes, 0 = no: ";
      cin>>specials;
      while(true){
	 for(int i = 0; i < specials.length(); i++){
	    if(!(specials.at(i) >= '0' && specials.at(i) <= '1')){
	       cout<<"Invalid input.\nDo you want special characters? 1 = yes, 0 = no: ";
	       cin>>specials;
	       i--;
	    }
	 }
	 break;
      }
      if(specials == "1")
      {
	 cout<<"What percentage of the password should be special characters? ";
	 cin>>specialPercent;
	 totalPercent += specialPercent;
      }

      if(totalPercent < 1 || totalPercent > 1)
      {
         cout<<"Invalid percentage."<<endl;
         continue;
      }

      int numUpper = (atoi(length.c_str())) * upperPercent;
      int numLower = (atoi(length.c_str())) * lowerPercent;
      int numNums = (atoi(length.c_str())) * numPercent;
      int numSpecial = (atoi(length.c_str())) * specialPercent;
      string password;
      for(int i = 0; i < numUpper; i++)
      {
	 char upper1 = (char) ((rand() % 26) + 65);
	 cout<<upper1;
	 password += upper1;
      }
      for(int i = 0; i < numLower; i++)
      {
	 char lower1 = (char) ((rand() % 26) + 97);
	 cout<<lower1;
	 password += lower1;
      }
      for(int i = 0; i < numNums; i++)
      {
	 char numbers1 =(char) ((rand() % 10) + 48);
	 cout<<numbers1;
	 password += numbers1;
      }
      for(int i = 0; i < numSpecial; i++)
      {
	 char special1 = (char) ((rand() % 13) + 33);
	 cout<<special1;
         password += special1;
      }
      cout<<endl;
      cout<<"Password: "<<password<<endl;
      while(true)
      {
	 cout<<"Continue? 1 = yes, 0 = no: ";
         cin>>cont;
	 if((cont == "1") || (cont == "0"))
	    break;
	 else
	    cout<<"Incorrect value."<<endl;
      }
   }
   return 0;
}

bool isint(string value){
   for(int i = 0; i < value.length(); i++){
      if(value.at(i) < '0' || value.at(i) > '9')
	 return false;
      else
	 return true;
   }
}
