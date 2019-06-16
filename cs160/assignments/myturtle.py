import turtle

window = turtle.Screen();
my_turtle = turtle.Turtle();
repeat = 1;

while(repeat == 1):
   while True:
      try:
         shape = int(input("Which shape would you like? \n1. Triangle \n2. Square \n3. Hexagon \n4. Octogon \n"""));
      except ValueError:
         print("Invalid input.");
         continue;
      if(shape < 1):
         print("Invalid input.");
         continue;
      elif(shape > 4):
         print("Invalid input.");
         continue;
      else:
         break;
   
   if(shape == 1):
      for a in range(3):
         my_turtle.forward(25);
         my_turtle.left(120);
   elif(shape == 2):
      for b in range(4):
         my_turtle.forward(25);
         my_turtle.left(90);
   elif(shape == 3):
      for c in range(6):
         my_turtle.forward(25);
         my_turtle.left(60);
   elif(shape == 4):
      for d in range(8):
         my_turtle.forward(25);
         my_turtle.left(45);
   
   while True:
      try:
         repeat = int(input("Continue? 1 = yes, 0 = no: "));
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
         window.clear();
         my_turtle = turtle.Turtle();
         break;

window.bye(); 
