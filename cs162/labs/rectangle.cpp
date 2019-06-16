#include "shape.h"
#include "rectangle.h"

rectangle::rectangle(){
   length = 0;
   width = 0;
}

rectangle::rectangle(double l, double w){
   length = l;
   width = w;
}

rectangle::~rectangle(){
}

rectangle::rectangle(const rectangle& r){
   length = r.length;
   width = r.width;
}

double rectangle::getLength(){
   return length;
}

double rectangle::getWidth(){
   return width;
}

void rectangle::setLength(double l){
   length = l;
}

void rectangle::setWidth(double w){
   width = w;
}

double rectangle::calcArea(){
   double area = length * width;
   return area;
}
