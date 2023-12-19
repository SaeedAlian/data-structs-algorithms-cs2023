#include <iostream>

#include "./Stack/Stack.h"

using namespace std;

bool stack_sequence_validation(int *pushed, int *popped, int length);

int main() {
  int pushed[] = {1, 3, 4, 5, 7};
  int popped[] = {1, 4, 3, 7, 5};

  bool is_valid = stack_sequence_validation(pushed, popped, 5);

  cout << (is_valid ? "Valid" : "Not Valid") << endl;

  return 0;
}

bool stack_sequence_validation(int *pushed, int *popped, int length) {
  Stack<int> stack;

  int j = 0;

  for (int i = 0; i < length; i++) {
    stack.push(pushed[i]);

    while (!stack.is_empty() && j < length && stack.get_top() == popped[j]) {
      stack.pop();
      j++;
    }
  }

  return stack.is_empty();
}
