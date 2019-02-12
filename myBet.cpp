#include <iostream>
#include <fstream>
#include<string>
#include "stack.h"
using namespace std;

struct BetNode
{
  char info;
  BetNode* left;
  BetNode* right;
};

void execute();
string inToPost(string input);
bool precedence(char top, char input);
int getWeight(char num);
bool isOperator(char input);
void fixToTree(string postfix);
void preorder(BetNode* tree);

int main()
{
  //Post: Execute the program
  execute();
  return 0;
}

void execute()
{ 
  //Post: Read from a file. Convert the info in file to postfix notation. Put postfix notation info into tree. Preorder travesrsal of tree.
  ifstream in("infix.dat");
  string input;
  if(!in)
  {
    cout << "Cannot open input file.\n";
  }
  
  while(in)
  {
    getline(in, input);
    string postfix = inToPost(input);  //Put into postfix notation
    fixToTree(postfix);                //Put postfix notation info into a binary expression tree
    cout << endl;
  }
}

string inToPost(string input)
{
  //Post: Convert an infix expression to postfix notation
  stack<char> b(30);
  string postfix = "";
  
  for(int i = 0;i<input.length();i++)
  {
    if(input[i] == '(')
    {
      b.push(input[i]);
      continue;
    }
    if(input[i] == ')')
    {
      while(!b.isEmpty() && b.top() != '(')
        postfix += b.topAndPop();
      if(!b.isEmpty())
        b.pop();
      
      continue;
    }
    if(isdigit(input[i]))
      postfix += input[i];
    else if(isOperator(input[i]))
    {
      if(b.isEmpty())
        b.push(input[i]);
      else
      {
        while(!b.isEmpty() && b.top() != '(' && precedence(b.top(), input[i]))
          postfix += b.topAndPop();
        b.push(input[i]);
      }
    }
  }
  while(!b.isEmpty())
    postfix += b.topAndPop();
  
  return postfix;
}

bool isOperator(char input)
{
  //Post: Determine if character is an operator
  if(input == '+' || input == '-' || input == '*' || input == '/')
    return true;
  else 
    return false;
}

bool precedence(char top, char input)
{
  //Post: determines if the input character has a lower precedence than the character at the top of the stack
  int weight1 = getWeight(top);
  int weight2 = getWeight(input);
  
  if(weight2 <= weight1)
    return true;
  else
    return false;
}

int getWeight(char num)
{
  //Post: Returns the weight of the operator
  switch(num)
  {
    case '/':
    case '*': return 2;
    case '+':
    case '-': return 1;
    default: return 0;
  }
}

void fixToTree(string postfix)
{
  //Post: Converts the postfix notation expression into a binary expression tree
  stack<BetNode*> a(30);
  
  for(int i = 0;i < postfix.length();i++)
  {
    if(isdigit(postfix[i]))
    {
      BetNode* newNode = new BetNode;
      newNode -> info = postfix[i];  newNode -> left = NULL;  newNode -> right = NULL;
      a.push(newNode);
    }
    else if(isOperator(postfix[i]))
    {
      BetNode* newNode = new BetNode;
      BetNode* ptr1 = a.topAndPop();
      BetNode* ptr2 = a.topAndPop();
      newNode -> info = postfix[i];  newNode -> left = ptr2;  newNode -> right = ptr1;
      a.push(newNode);
    }
  }
  preorder(a.top());
}

void preorder(BetNode* tree)
{
  //Post: Print the tree using preorder traversal
  if(tree != NULL)
  {
    cout << tree -> info << " ";
    preorder(tree -> left);
    preorder(tree -> right);
  }
}