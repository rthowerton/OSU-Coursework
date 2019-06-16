#ifndef ANIMAL_HEADER
#define ANIMAL_HEADER
class animal{
   protected:
      int age, cost, numBabies, foodCost;
   public:
      animal();
      void operator=(const animal&);
      int getAge();
      int getCost();
      int getNumBabies();
      int getFoodPrice();
      void setAge(int);
      void setCost(int);
      void setNumBabies(int);
      void setFoodPrice(int);
};
#endif
