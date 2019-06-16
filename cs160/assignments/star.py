import turtle;

window = turtle.Screen();
sr = turtle.Turtle();
cont = 1;

def star(x,y):
   for t in range(5):
      sr.forward(100);
      sr.right(144);

while cont == 1:

   sr.onclick(star);

   while True:
      try:
         cont = int(input("Continue? Yes = 1, No = 0: "));
      except ValueError:
         print("Invalid input.");
         continue;
      if(cont < 0 or cont > 1):
         print("Invalid input.");
         continue;
      else:
         window.clear();
         sr = turtle.Turtle();
         break;

turtle.bye();
