import math;

repeat = 1;
while repeat == 1:
   while True:
      try:
         weight = int(input("Enter the weight of the sphere: "));
         radius = int(input("Enter the radius of the sphere: "));
         break;
      except ValueError:
         print("Invalid input.");

   y = 62.4;
   V = (4.0/3.0) * math.pi * (radius**3);
   F = V * y;
   print("Buoyancy = ", end = "");
   print(F);

   if(F >= weight):
      print("The sphere will float.");
   else:
      print("The sphere will sink.");

   while True:
      try:
         repeat = int(input("Continue? Enter 1 if yes, 0 if no: "));
      except ValueError:
         print("Invalid input.");
         continue;
      if(repeat < 0):
         print("Invalid input.");
         continue;
      elif(repeat > 1):
         print("Invalid input.");
         continue;
      else:
         break;
