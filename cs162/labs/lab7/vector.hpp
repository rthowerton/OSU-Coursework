#include <stdlib.h>
#include <stdexcept>
template <class T>
class vector{
   private:
      T *v;
      int s;
   public:
      vector(){
	 s=0;
	 v=NULL;
      }

      ~vector(){
	 delete [] v;
      }

      vector(vector<T> &other){
	 s = other.s;
	 v = other.v;
      }

      void operator = (vector<T> &other){
	 s = other.s;
	 v = other.v;
      }

      T operator [] (int i){
	 return v[i];
      }

      T at(int i){
	 if(i < 0 || i >= s)
	    throw std::out_of_range("out of vector bounds");
	 else
	    return v[i];
      }

      int size(){
	 return s;
      }

      void push_back(T ele){
	 T *temp;
	 temp = new T[++s];
	 for(int i = 0; i < s-1; i++)
	    temp[i] = v[i];

	 delete [] v;
	 v = temp;
	 v[s-1] = ele;
      }
};
