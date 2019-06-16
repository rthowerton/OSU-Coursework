#ifndef SHAPE_HEADER
#define SHAPE_HEADER
#include <iostream>
using namespace std;
class shape{
   private:
      string name;
      string color;
   public:
      shape();
      shape(string, string);
      ~shape();
      shape(const shape&);
      virtual double calcArea() = 0;
      string getName();
      string getColor();
      void setName(string);
      void setColor(string);
};
#endif
