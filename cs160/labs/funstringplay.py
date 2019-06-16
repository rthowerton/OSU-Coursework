def num_matching_chars(strng1,strng2): 
   equal = 0;
   if(len(strng1) > len(strng2)):
      for x in range(len(strng2)-1):
         if(strng1[x] == strng2[x]):
            equal += 1;
   else:
      for x in range(len(strng1)-1):
         if(strng2[x] == strng1[x]):
            equal += 1;
   print("The number of equal characters is: " +str(equal+1));

#############################################################################################
#Function Name: percent_matching
#Description: Compare the characters of two strings to find the percentage of equal characters in the same positions
#Parameters: Two strings
#Pre-conditions: User has inputted two strings
#Post-conditions: None
#Return Values: None

def percent_matching(strng3,strng4):
   equal = 0;
   if(len(strng3) > len(strng4)):
      for x in range(len(strng4)-1):
         if(strng3[x] == strng4[x]):
            equal += 1;
   else:
      for x in range(len(strng3)-1):
         if(strng4[x] == strng3[x]):
            equal += 1;

   if(len(strng3) > len(strng4)):
      print("The percentage of equal characters is: " +str(((equal+1)/len(strng3))*100));
   else:
      print("The percentage of equal characters is: " +str(((equal+1)/len(strng4))*100));

#############################################################################################
#Function Name: main
#Description: Begin execution for program
#Parameters: None
#Pre-conditions: None
#Post-conditions: None
#Return Values: None

def main():
   inp1 = input("Enter something cool: ");
   inp2 = input("Enter something cooler: ");

   num_matching_chars(inp1,inp2);
   percent_matching(inp1,inp2);

main();
