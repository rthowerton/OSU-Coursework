import math;

while True:
   try:
      rep = int(input("Desired number of tests: "));
      break;
   except ValueError:
      print("Invalid input.");

if(rep < 0):
   rep *= -1;

while True:
   try:
      originum = int(input("Enter a positive whole number: "));
      break;
   except ValueError:
      print("Invalid input.");

if(originum < 0):
   originum *= -1;

guess = originum/2;

for x in range(rep):
   newnum = originum/guess;
   guess = (guess + newnum)/2;

print(guess);
print(math.sqrt(originum));
