num_scores = int(input("Enter the number of scores to be stored: "));
array = [0] * num_scores;

for x in range(num_scores):
   array[x] = int(input("Enter the score: "));
array.sort();
print(array);
avg = 0;
for x in range(num_scores):
   avg += array[x];
average = avg/num_scores;
print(average);

cont = 1
array2 = [0]
while(cont == 1):
   num = int(input("Enter a number: "));
   broke = False;
   for x in range(len(array2)):
      if(num==array2[x]):
         broke = True;
         print("Your number already exists.");
         break;
      else:
         continue;
   if(broke == False):
      array2.append(num);
      print("Your number has been added.");

   cont = int(input("Continue? 1 = yes, 0 = no: "));

print(array2);
