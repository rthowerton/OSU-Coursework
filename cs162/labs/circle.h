#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER
#define PI 3.14159265359

class circle : public shape{
   private:
      double radius;
   public:
      circle();
      circle(double);
      ~circle();
      circle(const circle&);
      double getRadius();
      void setRadius(double);
      double calcArea();
};
#endif
