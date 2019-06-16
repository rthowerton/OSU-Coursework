def is_balanced(s):
   #open_paren = 0;
   #for x in range(len(s)):
   #   if(not(x == (len(s)-1))):
   #      if(s[x] == ")" and open_paren == 0):
   #         return False
   #      elif(s[x] == ")"):
   #         open_paren -= 1;
   #      elif(s[x] == "("):
   #         open_paren += 1;
   #      else:
   #         return False;
   #   else:
   #      if(open_paren > 0):
   #         return False;
   #return True;
   parentheses = 0;
   for x in range(len(s)):
      if(s[x] == "("):
         parentheses += 1;
      if(s[x] == ")"):
         parentheses -= 1;
         if(parentheses < 0):
            return False;
   if(parentheses != 0):
      return False;
   return True;         

def main():
   paren = input("Give me da parentheses!!!! \n");
   if(is_balanced(paren)):
      print("Correct!");
   else:
      print("Wrong!");

main();
