#include "../Stack/Stack.h"

#include <iostream>
#include <string.h>

#define SEPERATOR ' '

int precedence(char op);
char *infix_to_postfix(char *infix);
int eval_postfix(char *postfix);

int main() {
  std::cout << "Enter operation : ";
  char *infix;

  std::cin >> infix;

  char *postfix = infix_to_postfix(infix);

  int result = eval_postfix(postfix);

  std::cout << "Result : " << result << std::endl;

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

  Stack<char> operators = Stack<char>(length);

  // We allocate double of the infix length because we need to add seperators
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

      postfix[j++] = SEPERATOR;

      while (!operators.is_empty() &&
             (last_operator = operators.pop_and_return()) != '(') {
        postfix[j++] = last_operator;
        postfix[j++] = SEPERATOR;
      }

      break;
    }

    case '+':
    case '-':
    case '*':
    case '/': {
      char top_operator = operators.get_top();

      if (infix[i - 1] != ')') {
        postfix[j++] = SEPERATOR;
      }

      while (!operators.is_empty() &&
             precedence(top_operator) >= precedence(symbol)) {
        postfix[j++] = operators.pop_and_return();
        postfix[j++] = SEPERATOR;
        top_operator = operators.get_top();
      }

      operators.push(symbol);

      break;
    }
    }
  }

  if (!operators.is_empty()) {
    postfix[j++] = SEPERATOR;
  }

  while (!operators.is_empty()) {
    postfix[j++] = operators.pop_and_return();
    postfix[j++] = SEPERATOR;
  }

  postfix[j] = '\0';

  return postfix;
}

int eval_postfix(char *postfix) {
  int length = strlen(postfix);

  Stack<int> operands = Stack<int>(length);

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
        character == SEPERATOR) {
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
