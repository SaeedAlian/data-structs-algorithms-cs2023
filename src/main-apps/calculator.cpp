#include "../Stack/Stack.h"

#include <iostream>
#include <string.h>

#define SEPERATOR ' '

int precedence(char op);
char *infix_to_postfix(char *infix);
double eval_postfix(char *postfix);

int main() {
  std::cout << "Enter operation : ";
  char *infix;

  std::cin >> infix;

  char *postfix = infix_to_postfix(infix);

  double result = eval_postfix(postfix);

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

    if ((symbol >= '0' && symbol <= '9') || symbol == '.') {
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

      // Adds the previous operators to postfix, until it reaches the open
      // parenthese.
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

      // Add seperator if the prev char was not ')'
      // If we didn't wrote this, then the postfix would have two seperators
      // after an operator which comes after a pair of parentheses.
      if (infix[i - 1] != ')') {
        postfix[j++] = SEPERATOR;
      }

      // Add the operators of the operators stack, if the top operator has
      // greater precedence value than the current operator inside the infix.
      // Also pop the operator from the stack after insertion inside the
      // postfix.
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

  // If the operators weren't empty then add a seperator because we want to add
  // the operator to postfix. It adds the seperator for the first operator.
  if (!operators.is_empty()) {
    postfix[j++] = SEPERATOR;
  }

  // Add the remaining operators inside the stack.
  while (!operators.is_empty()) {
    postfix[j++] = operators.pop_and_return();
    postfix[j++] = SEPERATOR;
  }

  postfix[j] = '\0';

  return postfix;
}

double eval_postfix(char *postfix) {
  int length = strlen(postfix);

  Stack<double> operands = Stack<double>(length);

  if (length == 0)
    return 0;

  // temp_operand is the current operand token that we are reading from the
  // postfix.
  double temp_operand = 0;

  // temp_decimal is the current operand token that we are reading from the
  // postfix. but only the decimal part in this separate variable.
  double temp_decimal = 0;

  // This flag will indicate that we are reading the whole part of the number or
  // the decimals
  bool calculate_decimals = false;

  for (int i = 0; postfix[i] != '\0'; i++) {
    int character = postfix[i];

    if (character == '.') {
      calculate_decimals = true;
      continue;
    }

    if (character >= '0' && character <= '9') {
      if (calculate_decimals) {
        temp_decimal = (character - '0') + temp_decimal * 10;
      } else {
        temp_operand = (character - '0') + temp_operand * 10;
      }

      continue;
    }

    if (character == SEPERATOR) {
      if (postfix[i - 1] >= '0' && postfix[i - 1] <= '9') {
        // divide the decimal part until it reaches less than 1,
        // so it will become the main decimal part of the current number token
        // that we are reading.
        while (temp_decimal >= 1) {
          temp_decimal /= 10;
        }

        operands.push(temp_operand + temp_decimal);

        temp_operand = 0;
        temp_decimal = 0;
        calculate_decimals = false;
      }

      continue;
    }

    switch (character) {
    case '+': {
      double a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b + a);

      break;
    }

    case '-': {
      double a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b - a);

      break;
    }

    case '*': {
      double a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b * a);

      break;
    }

    case '/': {
      double a, b;
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
