#include <iostream>
#include <stdlib.h>
using namespace std;

// definition of Stack class
class Stack {
  public:
    char exp[100];
    int top;

    // Constructor
    Stack(){top = -1;}

    // function prototypes
    bool push(char item);
    char pop();
};

// push function
bool Stack::push(char item) {
  // if the stack is full, return false
  if (top >= 99) {
    cout << "Stack Overflow" << endl;
    return false;
  }
  // if stack is not full, increment top, set top of stack to the item being pushed in
  else {
    top++;
    exp[top] = item;
    return true;
  }
}

// pop function
char Stack::pop() {
  // if stack is empty, return. 
  if (top == -1) {
    cout << "Stack Underflow" << endl;
    return 0;
  }
  // is stack isn't empty, remove a value from the stack and return that value
  else {
    return exp[top--];
  }
}

// checks if 2 values are a matching pair of brackets or parenthesis
int isMatchingPair(char char1, char char2) {
  if (char1 == '(' && char2 == ')') {
    return 1;
  }
  else if (char1 == '{' && char2 == '}') {
    return 1;
  }
  else if (char1 == '[' && char2 == ']') {
    return 1;
  }
  else {
    return 0;
  }
}

// checks if there is a closing bracket for every open bracket and vice versa
int areParenthesisBalanced(char exp[]) {
  // creates stack object with pointer s
  Stack* s = new Stack();

  int i = 0;
  // traverse through expression
  while(exp[i]) {
    if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') { // if open push to stack
      s->push(exp[i]);
    }
    if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') { // if close ...
      if (s->top == -1) { // check if empty
        return 0; // if empty return false
      }
      else if (!isMatchingPair(s->pop(), exp[i])) { // check if not matching pair
        return 0; // if not matching pair return false
      }
    }
    i++;
  }

  // if stack is empty, return true (balanced)
  if (s->top == -1) {
    return 1;
  }
  // if stack is not empty, return false (unbalanced)
  else {
    return 0;
  }
}

int main() {
  // char array for entered expression
  char exp[100]; 

  // prompt user to enter expression
  cout << "Enter the expression:" << endl;
  // read expression (input) from user
  cin >> exp;

  // check if parenthesis are balanced
  if (areParenthesisBalanced(exp)) {
    cout << "Balanced";
  }
  else {
    cout << "Not Balanced";
  }
}
