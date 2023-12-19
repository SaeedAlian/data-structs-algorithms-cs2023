#include <string.h>

#include <iostream>

#include "./Stack/Stack.h"

using namespace std;

char *prefix_to_postfix(char *prefix);

int main() {
  cout << "Enter prefix : ";
  char *prefix;
  cin >> prefix;

  char *postfix = prefix_to_postfix(prefix);

  cout << "The postfix is : " << postfix;

  delete postfix;

  return 0;
}

char *prefix_to_postfix(char *prefix) {
  int length = strlen(prefix);

  Stack<char> operators;

  int operand_count = 0;

  char *postfix = new char[length];
  int j = 0;

  for (int i = 0; prefix[i] != '\0'; i++) {
    char symbol = prefix[i];

    if (operand_count >= 2 && !operators.is_empty()) {
      operand_count = 0;
      postfix[j++] = operators.pop_and_return();
    }

    if (symbol >= '0' && symbol <= '9') {
      operand_count++;
      postfix[j++] = symbol;
      continue;
    }

    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
      operand_count = 0;
      operators.push(symbol);
      continue;
    }
  }

  while (!operators.is_empty()) {
    postfix[j++] = operators.pop_and_return();
  }

  postfix[j] = '\0';

  return postfix;
}
