#include <iostream>
using namespace std;
#include "shape.h"

shape::shape(){
   name = "shape";
   color = "colorless";
}

shape::shape(string n, string c){
   name = n;
   color = c;
}

shape::~shape(){
}

shape::shape(const shape& s){
   name = s.name;
   color = s.color;
}

string shape::getName(){
   return name;
}

string shape::getColor(){
   return color;
}

void shape::setName(string n){
   name = n;
}

void shape::setColor(string c){
   color = c;
}
