import turtle;

window = turtle.Screen();
nm = turtle.Turtle();
cont = 1;

def space():
   nm.up();
   nm.fd(30);
   nm.down();

def ahr():
   nm.left(90);
   nm.fd(100);
   nm.right(90);
   nm.fd(50);
   nm.right(90);
   nm.fd(50);
   nm.right(90);
   nm.fd(50);
   nm.left(135);
   nm.fd(70);
   nm.left(45);

def wy():
   nm.left(90);
   nm.fd(50);
   nm.back(50);
   nm.right(90);
   nm.fd(50);
   nm.left(90);
   nm.fd(50);
   nm.back(100);
   nm.left(90);
   nm.fd(50);
   nm.back(50);
   nm.right(90);
   nm.fd(50);
   nm.right(90);

def ay():
   nm.left(90);
   nm.fd(50);
   nm.right(90);
   nm.fd(50);
   nm.left(90);
   nm.fd(25);
   nm.left(90);
   nm.fd(50);
   nm.back(50);
   nm.right(90);
   nm.back(75);
   nm.left(90);
   nm.fd(50);
   nm.back(50);
   nm.right(180);

def ehn():
   nm.left(90);
   nm.fd(65);
   nm.back(15);
   nm.right(90);
   nm.fd(50);
   nm.right(90);
   nm.fd(50);

def name(x,y):
   ahr();
   space();
   wy();
   space();
   ay();
   space();
   ehn();

while cont == 1:
   nm.onclick(name);
   while True:
      try:
         cont = int(input("Continue? Yes = 1, no = 0: "));
      except ValueError:
         print("Invalid input.");
         continue;
      if(cont < 0 or cont > 1):
         print("Invalid input.");
         continue;
      else:
         window.clear();
         nm = turtle.Turtle();
         break;

turtle.bye();
