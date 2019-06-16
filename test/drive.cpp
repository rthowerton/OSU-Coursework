#include <iostream>
#include <string>
using namespace std;
#include "car.h"

int main(){
   int y, s;
   string m;
   cout<<"Enter the year of your car:"<<endl;
   cin>>y;
   cout<<"Enter the make of your car:"<<endl;
   cin>>m;
   cout<<"Enter the current speed of your car:"<<endl;
   cin>>s;
   car vehicle(y, m, s);
   for(int i = 0; i < 5; i++){
      vehicle.accelerate();
      cout<<"Current speed: "<<vehicle.getSpeed()<<endl;
      cout<<"Make of car: "<<vehicle.getMake()<<endl;
      cout<<"Year of car: "<<vehicle.getYear()<<endl;
   }
   return 0;
}
