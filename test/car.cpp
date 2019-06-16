#include <iostream>
#include <cstring>
using namespace std;
#include "car.h"

car::car(int y, string m, int s){
   year = y;
   make = m;
   speed = s;
}

int car::getYear(){
   return year;
}

string car::getMake(){
   return make;
}

int car::getSpeed(){
   return speed;
}

void car::accelerate(){
   speed += 5;
}

