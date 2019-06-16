#include <iostream>
#include <string>
using namespace std;
class car{
   private:
      int year;
      string make;
      int speed;
   public:
      car(int, string, int);
      int getYear();
      string getMake();
      int getSpeed();
      void accelerate();
};
