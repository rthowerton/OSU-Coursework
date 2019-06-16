#include <iostream>
using namespace std;
#include "shape.h"
#include "circle.h"
#include "rectangle.h"

void printShapeInfo(shape& s){
   cout<<"Shape name: "<<s.getName()<<endl;
   cout<<"Shape color: "<<s.getColor()<<endl;
   cout<<"Shape area: "<<s.calcArea()<<endl;
}

int main(){
   circle c(3);
   c.setName("circle1");
   c.setColor("blue");
   rectangle r(4, 2);
   r.setName("rectangle1");
   r.setColor("red");
   printShapeInfo(c);
   printShapeInfo(r);
   return 0;
}
