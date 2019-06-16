#include <math.h>
#include "shape.h"
#include "circle.h"

circle::circle(){
   radius = 0;
}

circle::circle(double r){
   radius = r;
}

circle::~circle(){
}

circle::circle(const circle& c){
   radius = c.radius;
}

double circle::getRadius(){
   return radius;
}

void circle::setRadius(double r){
   radius = r;
}

double circle::calcArea(){
   double area = PI * pow(radius, 2);
   return area;
}
