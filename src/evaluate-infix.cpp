#include <string.h>

#include <iostream>

#include "./Stack/Stack.h"

#define SPECIAL_CHARACTER '$'

using namespace std;

int precedence(char op);
char *infix_to_postfix(char *infix);
int eval_postfix(char *postfix);

int main() {
  cout << "Enter operation : ";
  char *infix;

  cin >> infix;

  char *postfix = infix_to_postfix(infix);

  cout << "The postfix is : ";
  cout << postfix << endl;

  int result = eval_postfix(postfix);

  cout << "The result is : " << result << endl;

  delete postfix;

  return 0;
}

int precedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;

  case '*':
  case '/':
    return 2;

  default:
    return 0;
  }
}

char *infix_to_postfix(char *infix) {
  int length = strlen(infix);

  Stack<char> operators;

  char *postfix = new char[length * 2];
  int j = 0;

  for (int i = 0; infix[i] != '\0'; i++) {
    char symbol = infix[i];

    if (symbol >= '0' && symbol <= '9') {
      postfix[j++] = symbol;
      continue;
    }

    switch (symbol) {
    case '(': {
      operators.push(symbol);

      break;
    }

    case ')': {
      int last_operator;

      postfix[j++] = SPECIAL_CHARACTER;

      while (!operators.is_empty() &&
             (last_operator = operators.pop_and_return()) != '(') {
        postfix[j++] = last_operator;
        postfix[j++] = SPECIAL_CHARACTER;
      }

      break;
    }

    case '+':
    case '-':
    case '*':
    case '/': {
      char top_operator = operators.get_top();

      if (infix[i - 1] != ')') {
        postfix[j++] = SPECIAL_CHARACTER;
      }

      while (!operators.is_empty() &&
             precedence(top_operator) >= precedence(symbol)) {
        postfix[j++] = operators.pop_and_return();
        postfix[j++] = SPECIAL_CHARACTER;
        top_operator = operators.get_top();
      }

      operators.push(symbol);

      break;
    }
    }
  }

  if (!operators.is_empty()) {
    postfix[j++] = SPECIAL_CHARACTER;
  }

  while (!operators.is_empty()) {
    postfix[j++] = operators.pop_and_return();
    postfix[j++] = SPECIAL_CHARACTER;
  }

  postfix[j] = '\0';

  return postfix;
}

int eval_postfix(char *postfix) {
  int length = strlen(postfix);

  Stack<int> operands;

  if (length == 0)
    return 0;

  int tempOperand = 0;

  for (int i = 0; postfix[i + 1] != '\0'; i++) {
    int character = postfix[i];

    if (character >= '0' && character <= '9') {
      tempOperand = (character - '0') + tempOperand * 10;

      continue;
    }

    if (postfix[i - 1] >= '0' && postfix[i - 1] <= '9' &&
        character == SPECIAL_CHARACTER) {
      operands.push(tempOperand);
      tempOperand = 0;

      continue;
    }

    switch (character) {
    case '+': {
      int a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b + a);

      break;
    }

    case '-': {
      int a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b - a);

      break;
    }

    case '*': {
      int a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b * a);

      break;
    }

    case '/': {
      int a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b / a);

      break;
    }

    default:
      continue;
    }
  }

  return operands.pop_and_return();
}
