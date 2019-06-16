strng1 = input("Enter something cool: ");
length = 0;
print(strng1);

while(length < len(strng1)):
   length += 1;
print(strng1[0],end = "");
print(strng1[length-1]);

for x in range(len(strng1)):
   print(strng1[x]);
