#include <iostream>
#include <stdexcept>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "sexceptions.h"

using namespace std;

void menu();
bool isOperator(char input);
void execute(string input, stack<int> &a);
void posPrint(int input);
void negPrint(char input);
void operateAndPrint(stack<int> &a, char input);

int main()
{
  //Post: This method calls the menu of the program
  menu();
  return 0;
}

void menu()
{
  //Post: This method asks the user for input of a string. After the user is done entering, the program will call the execute function to run.

  stack<int> a(15);  char quit;  string input;

  do
  {
    cout << "***************** THE POSTFIX EVALUATOR *****************\n";
    cout << "Your RPN Expression: ";
    
    getline(cin, input, ';');
    
    execute(input, a);
    
    cout << "Go again? (Y/N) ";
    cin >> quit;
  } while(toupper(quit) != 'N');
}

void execute(string input, stack<int> &a)
{
  //Post: This function exectutes the program

  const char* b = input.c_str();
  int n = 0;
  
  try      //Test for invalid input
  {
    while(*b != '\0')
    {
      if(isdigit(*b) && isOperator(*b) && *b != '_')
        throw "You have entered an Invalid Expression -- Now Exiting";
      else
      {
        n++;
        b++;
      }
    }
  }
  catch(const char* msg)
  {
    cout << msg << endl;
    exit(0);
  }
  
  for(int i = 0; i < n; i++)
  {
    if(input[i] == '_')    //Operation for negative numbers
    {
      a.push((input[i+1]-'0')* -1);
      negPrint(input[i+1]); 
    }
    if((isdigit(input[i]) && input[i-1] != '_') || (isdigit(input[i]) && i == 0))  //Operation for positive numbers
    {
      int operand = 0;
      while(i < input.length() && isdigit(input[i]))
      {
        operand = (operand*10) + (input[i]-'0');
        i++;
      }
      i--;
      a.push(operand);
      posPrint(operand);
    }
    if(isOperator(input[i]) && (i != 0 || 1 != 1))    //Operation for operators
      operateAndPrint(a, input[i]);
  }
  cout << "Token = ;\t" << "Pop " << a.topAndPop() << endl << endl;    //Final output
}

bool isOperator(char input)
{
  //Post: Determine if character is an operator
  if(input == '+' || input == '-' || input == '*' || input == '/')
    return true;
  else 
    return false;
}

void operateAndPrint(stack<int> &a, char input)
{
  //Post: This method performs a mathematical operation depending on the operator
  try
  {
    int num1 = a.topAndPop();  int num2 = a.topAndPop();
    
    cout << "Token = " << input << "\t";
    cout << "Pop " << num1 << "\t";
    cout << "Pop " << num2 << "\t";
    
    if(input == '/')    //Divide two numbers
    {
      cout << "Push " << num2/num1 << endl;
      a.push(num2/num1);
      
      if(num1 == '0')
        throw "Division by Zero Exception -- Now Exiting.";
    }
    if(input == '*')    //Multiply two numbers
    {
      cout << "Push " << num2*num1 << endl;
      a.push(num1*num2);
    }
    if(input == '+')    //Add two numbers
    {
      cout << "Push " << num2+num1 << endl;
      a.push(num1 + num2);
    }
    if(input == '-')    //Subtract two numbers
    {
      cout << "Push " << num2-num1 << endl;
      a.push(num2 - num1);
    }
  }
  catch(const char* msg)
  {
    cout << msg << endl;
    exit(0);
  }
}

void posPrint(int input)
{
    //Post: Print a positive number
    cout << "Token = " << input << "\t";
    cout << "Push " << input << endl;
}

void negPrint(char input)
{
    //Post: Print a negative number
    cout << "Token = -" << input << "\t";
    cout << "Push -" << input << endl;
}