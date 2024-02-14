/*
  Project1.cpp
  Ryan Thompson
  COP4415
  Last Modified: 10/21/2022
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
using namespace std;

#define MAX 100

// class def
class Stack {

  public:
     int top;
     char exp[MAX]; 

  Stack() {
   top = -1; 
  }

  // function prototypes
  bool push(char item);
  char pop();
  char peek(); 
  bool isEmpty();
};

// push function
bool Stack::push(char item) {
   if (top >= (MAX - 1)) {
    cout << "Stack Overflow";
    return false;
  }
   else {
    top++;
    exp[top] = item;
    return true;
  }
}

// pop function
char Stack::pop() {
  if(top == -1) {
    return 0;
  } 
  else {
    char c = exp[top];
    top--;
    return c;
  } 
}

// function to return top of stack
char Stack::peek() {
   if (top < 0) {
     cout << "Stack is Empty"; 
     return 0;
   }
  else {
    char c = exp[top];
    return c;
  }
}

// function to check if stack is empty
bool Stack::isEmpty() {
   return (top < 0);
}

// returns a value showing the priority of the operator
int prec(char c) {
  if (c == '+' || c == '-') {
    return 1;
  }
  else if (c == '*' || c == '/') {
    return 2;
  }
  else {
    return -1;
  }
}

int evaluatePostfix(string exp){
  Stack stack;

  // traverse expression
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] >= '0' && exp[i] <= '9') { // if the char is an operand, push to stack 
      stack.push(exp[i] - '0'); 
    }
    else { // if the char is an operator, push to stack
      int a = stack.peek();
      stack.pop();
      int b = stack.peek();
      stack.pop();

      switch (exp[i]) {
        case '+':
               stack.push(b + a);
               break;
          case '-':
               stack.push(b - a);
               break;
          case '*':
               stack.push(b * a);
               break;
          case '/':
               stack.push(b / a);
               break;
      }
    }
  }
  return stack.peek(); // return result
}

// function to translate infix expression to postfix expression
string infixToPostFix(string infix) { 
  Stack stack; // stack to hold operators
  string postfix; // postfix string to be returned

  for (int i = 0; i < infix.length(); i++) {
    char ch = infix[i];

    // if char is operator, add to postfix
    if ( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
      postfix += ch;
    }

    // if char is (, push to stack
    else if (ch == '(') {
      stack.push('(');
    }

    // if char is ), push pop until )
    else if (ch == ')') {
      while (stack.peek() != '(') {      
        postfix += stack.peek();
        stack.pop();
        }
      
      stack.pop();
    }

    // if char is operator, pop from stack and add to postfix
    else {
      while (!stack.isEmpty() && prec(infix[i]) <= prec(stack.peek())){
        postfix += stack.peek();
        stack.pop();
      }
      
      stack.push(ch);
    }
  }

  // pop all elements from stack
  while (!stack.isEmpty()) {
    postfix += stack.peek();
    stack.pop();
  }
  
  return postfix;
}

int main() {
  cout << "Enter a string:" << endl;
  string exp;
  cin>>exp;
  string postfix;
  int evaluation;
  postfix = infixToPostFix(exp);
  cout << postfix << endl;
  evaluation = evaluatePostfix(postfix);
  cout << evaluation << endl;
  return 0;
}
