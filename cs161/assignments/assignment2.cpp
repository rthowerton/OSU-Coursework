/*******************************
 * Program: assignment2.cpp
 * Author: Ryan Howerton
 * Date: 1/18/2016
 * Description: calculate 3 different financial actions: loan balance, continuously compounded interest, or future value using a switch statement and cmath.
 * Input: only user input to fill variables
 * Output: results of calculations
******************************/
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main()
{
   int calculate;
   //ask which calculation to make
   cout<<"What would you like to calculate?\n1 - Loan Balance\n2 - Continuously Compounded Interest\n3 - Future Value\nSelection: ";
   cin>>calculate;
   //perform calculation depending on user input
   switch(calculate)
   {
      //case 1: calculate loan balance.
      case 1:
         //all variables to use in calculation
         double investment1;
         int pay_period1;
         double interest1;
         double payment1;
         int num_payments1;
         double result1;
         double goal1;
         //get user inputs and fill variables
         cout<<"Initial investment: ";
         cin>>investment1;
         cout<<"Payments per year: ";
         cin>>pay_period1;
         cout<<"Interest rate: ";
         cin>>interest1;
         interest1 = interest1/pay_period1;
         cout<<"Amount payed per period: ";
         cin>>payment1;
         cout<<"Number of payments made: ";
         cin>>num_payments1;
         cout<<"Your goal for this loan: ";
         cin>>goal1;
         //calculations
         cout<<"Your goal was: "<<goal1<<endl;
         result1 = investment1*pow((1+interest1), num_payments1) - (payment1/interest1)*(pow((1+interest1), num_payments1) - 1);
         cout<<"You owe $"<<result1<<endl;
         if(result1 > goal1)
            cout<<"You will not meet your goal."<<endl;
         else
            cout<<"You will meet your goal."<<endl;
         break;
      //case 2: calculate continuously compounded interest
      case 2:
         //all variables
         double investment2;
         double interest2;
         double years2;
         double result2;
         double goal2;
         //get user input
         cout<<"Principle investment: ";
         cin>>investment2;
         cout<<"Annual interest rate: ";
         cin>>interest2;
         cout<<"Years compounding: ";
         cin>>years2;
         cout<<"Your goal for this investment: ";
         cin>>goal2;
         //calcuations
         cout<<"Your goal was: "<<goal2<<endl;
         result2 = investment2*pow(M_E,interest2*years2);
         cout<<"Your investment is worth $"<<result2<<endl;
         if(result2 < goal2)
            cout<<"You will not meet your goal."<<endl;
         else
            cout<<"You will meet your goal."<<endl; 
         break;
      //case 3: calculate future value
      case 3:
         //all variables
         double cashmoney;
         double returnrate;
         int num_periods;
         double result3;
         double goal3;
         //user input
         cout<<"Starting cash flow: ";
         cin>>cashmoney;
         cout<<"Rate of return: ";
         cin>>returnrate;
         cout<<"Number of periods: ";
         cin>>num_periods;
         cout<<"Your value goal: ";
         cin>>goal3;
         //calculations
         cout<<"Your goal was: "<<goal3<<endl;
         result3 = cashmoney*pow(1+returnrate, num_periods);
         cout<<"Future Value = $"<<result3<<endl;
         if(result3 < goal3)
            cout<<"You will not meet your goal."<<endl;
         else
            cout<<"You will meet your goal."<<endl; 
         break;
      default:
         cout<<"Error: Invalid input."<<endl;
         break;
   }
   return 0;
}
