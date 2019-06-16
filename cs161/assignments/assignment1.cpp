#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

int main()
{
   /*practice with using pi and trigonometric functions*/
   cout<<cos(2*M_PI/3)<<endl;
   cout<<2*sin(2*M_PI/3)<<endl;
   cout<<tan(-3*M_PI/4)<<endl;
   /*practice with log functions*/
   cout<<log10(55)<<endl;
   cout<<log(60)<<endl;
   /*practice using log functions of different bases*/
   cout<<"log_2(15) = ln(15) / ln(2) = "<<(log(15))/(log(2))<<endl;
   cout<<"log_4(40) = ln(40) / ln(4) = "<<(log(40))/(log(4))<<endl;
   /*power functions and trigonometry*/
   cout<<"sin(1) = "<<sin(1)<<", sin(10) = "<<sin(10)<<", sin(100) = "<<sin(100)<<endl;
   cout<<"3^sin(1) = "<<pow(3, sin(1))<<endl;
   cout<<"3^sin(10) = "<<pow(3, sin(10))<<endl;
   cout<<"3^sin(100) = "<<pow(3, sin(100))<<endl;
   /*more complicated log functions*/
   cout<<"(x = 1); ln((1^2) + 1)/ln(2) = ln(2)/ln(2) = 1"<<endl;
   cout<<"(x = 10); ln((10^2) + 1)/ln(2) = ln(101)/ln(2) = "<<log(101)/log(2)<<endl;
   cout<<"(x = 100); ln((100^2) + 1)/ln(2) = ln(10001)/ln(2) = "<<log(10001)/log(2)<<endl;
   /*climits stuff*/
   cout<<"Signed int max: "<<INT_MAX<<endl;
   cout<<"Signed int min: "<<INT_MIN<<endl;
   cout<<"Unsigned int max: "<<UINT_MAX<<endl;
   cout<<"Signed long max: "<<LONG_MAX<<endl;
   cout<<"Signed long min: "<<LONG_MIN<<endl;
   cout<<"Unsigned long max "<<ULONG_MAX<<endl;
   cout<<"Signed short max: "<<SHRT_MAX<<endl;
   cout<<"Signed short min: "<<SHRT_MIN<<endl;
   cout<<"Unsigned short max: "<<USHRT_MAX<<endl;
   /*climits math*/
   int lsint = (int) pow(2, sizeof(int)*8)-1;
   int ssint = (int) pow(-2, sizeof(int)*8)+1;
   unsigned int ulint = (unsigned int) pow(2, sizeof(unsigned int)*8)-1;
   long lslong = (long) pow(2, sizeof(long)*8)-1;
   long sslong = (long) pow(-2, sizeof(long)*8)+1;
   unsigned long ullong =(unsigned long) pow(2, sizeof(unsigned long)*8)-1;
   short lsshort = pow(2, sizeof(short)*8-1)-1;
   short ssshort = pow(-2, sizeof(short)*8-1);
   unsigned short ulshort = (unsigned short) pow(2, sizeof(unsigned short)*8)-1;
   /*print calculated values*/
   cout<<"Calculated signed int max: "<<lsint<<endl;
   cout<<"Calculated signed int min: "<<ssint<<endl;
   cout<<"Calculated unsigned int max: "<<ulint<<endl;
   cout<<"Calculated signed long max: "<<lslong<<endl;
   cout<<"Calculated signed long min: "<<sslong<<endl;
   cout<<"Calculated unsigned long max: "<<ullong<<endl;
   cout<<"Calculated signed short max: "<<lsshort<<endl;
   cout<<"Calculated signed short min: "<<ssshort<<endl;
   cout<<"Calculated unsigned short max: "<<ulshort<<endl;
   return 0;
}
