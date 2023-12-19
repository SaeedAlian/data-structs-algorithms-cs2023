#include <iostream>

#include "./Stack/Stack.h"

using namespace std;

bool check_expression_balance(string expression);

int main() {
  string input;

  cout << "Enter expression : ";
  cin >> input;

  bool is_balanced = check_expression_balance(input);

  cout << (is_balanced ? "The expression is balanced."
                       : "The expression is not balanced.")
       << endl;

  return 0;
}

bool check_expression_balance(string expression) {
  Stack<char> stack;

  bool is_balanced = true;

  for (int i = 0; is_balanced && expression[i] != '\0'; i++) {
    switch (expression[i]) {
    case '(':
    case '[':
    case '{':
      stack.push(expression[i]);
      break;

    case ')':
      if (stack.get_top() != '(' || stack.is_empty()) {
        is_balanced = false;
      } else {
        stack.pop();
      }

      break;

    case '}':
      if (stack.get_top() != '{' || stack.is_empty()) {
        is_balanced = false;
      } else {
        stack.pop();
      }

      break;

    case ']':
      if (stack.get_top() != '[' || stack.is_empty()) {
        is_balanced = false;
      } else {
        stack.pop();
      }

      break;

    default:
      break;
    }
  }

  if (!stack.is_empty())
    is_balanced = false;

  return is_balanced;
}
