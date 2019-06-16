#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

class rectangle : public shape{
   private:
      double length;
      double width;
   public:
      rectangle();
      rectangle(double, double);
      ~rectangle();
      rectangle(const rectangle&);
      double getLength();
      double getWidth();
      void setLength(double);
      void setWidth(double);
      double calcArea();
};
#endif
