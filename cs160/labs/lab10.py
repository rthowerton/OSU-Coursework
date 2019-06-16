def is_int(s):
   for x in range(len(s)):
      if(not s[x].isnumeric()):
         return False;
   return True;

def sing_song(n):
   while(n > 0):
      print(str(n) +" bottles of beer on the wall, "+ str(n) +" bottles of beer; take one down, pass it around "+ str(n-1) +" bottles of beer on the wall!");
      n -= 1;

def main():
   verses = input("How many verses do you want sung? \n");
   if(is_int(verses)):
      sing_song(int(verses));
   else:
      print("Wrong.");

main();
