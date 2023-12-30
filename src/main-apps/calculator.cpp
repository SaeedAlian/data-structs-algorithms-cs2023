#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

#include <cmath>
#include <iostream>
#include <string.h>

#define SEPERATOR ' '

#define LN_TOKEN "ln"
#define SIN_TOKEN "sin"
#define COS_TOKEN "cos"
#define TAN_TOKEN "tan"

typedef long double ld;

int precedence(char op);
char *infix_to_postfix(char *infix);
ld eval_postfix(char *postfix);
ld eval_postfix_token(std::string token, ld operand);

int main() {
  std::cout << "Enter operation : ";
  char *infix;

  std::cin >> infix;

  char *postfix = infix_to_postfix(infix);

  std::cout << "Postfix : " << postfix << std::endl;

  ld result = eval_postfix(postfix);

  std::cout << "Result : " << result << std::endl;

  delete postfix;

  return 0;
}

int factorial(int x) {
  int res = 1;

  for (int i = x; i > 0; i--) {
    res *= i;
  }

  return res;
}

int precedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;

  case '*':
  case '/':
    return 2;

  case '^':
    return 3;

  default:
    return 0;
  }
}

char *infix_to_postfix(char *infix) {
  int length = strlen(infix);

  Stack<char> operators = Stack<char>(length);
  Queue<std::string> tokens_q = Queue<std::string>(length);

  std::string tokens[] = {LN_TOKEN, SIN_TOKEN, COS_TOKEN, TAN_TOKEN};

  // We allocate ld of the infix length because we need to add seperators
  char *postfix = new char[length * 2];
  int j = 0;

  // Count the index of current token
  int token_index = 0;

  bool is_inserting_token = false;

  for (int i = 0; infix[i] != '\0'; i++) {
    char symbol = infix[i];

    /*
     * If we are not inserting any token, then we need to
     * check the first character of all tokens for any matching,
     * then if we find a match, we will add it to the tokens queue.
     * Also you can see after this block we increment the token_index if
     * the queue is not empty, so in the next iteration, we check the
     * queue instead of all tokens, and then perform the same algorithm.
     */
    if (!is_inserting_token) {
      if (token_index == 0) {
        for (int i = 0; i < 4; i++) {
          if (symbol == tokens[i][token_index]) {
            tokens_q.enqueue(tokens[i]);
            postfix[j++] = symbol;

            if (tokens[i][token_index + 1] == '\0') {
              is_inserting_token = true;
            }
          }
        }
      } else {
        std::string current_token;

        bool match_found = false;

        while (!tokens_q.is_empty() && !match_found && !is_inserting_token) {
          tokens_q.dequeue(current_token);

          if (symbol == current_token[token_index]) {
            tokens_q.enqueue(current_token);
            postfix[j++] = symbol;

            if (current_token[token_index + 1] == '\0') {
              is_inserting_token = true;
            }

            match_found = true;
          }
        }
      }
    }

    if (!is_inserting_token) {
      if (!tokens_q.is_empty()) {
        token_index++;
      } else {
        while (token_index > 0) {
          j--;
          token_index--;
        }
      }
    }

    if ((symbol >= '0' && symbol <= '9') || symbol == '.' || symbol == '!') {
      postfix[j++] = symbol;
      continue;
    }

    switch (symbol) {
    case '(': {
      // Insert the opening parenthese of the token.
      if (is_inserting_token) {
        postfix[j++] = symbol;
        break;
      }

      operators.push(symbol);

      break;
    }

    case ')': {
      // Close the parenthese of token, then reset all the values that are
      // related to tokens.
      if (is_inserting_token) {
        is_inserting_token = false;
        token_index = 0;

        while (!tokens_q.is_empty()) {
          tokens_q.dequeue();
        }

        postfix[j++] = symbol;
        postfix[j++] = SEPERATOR;

        break;
      }

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
    case '/':
    case '^': {
      if (is_inserting_token) {
        break;
      }

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

ld eval_postfix(char *postfix) {
  int length = strlen(postfix);

  Stack<ld> operands = Stack<ld>(length);
  Queue<std::string> tokens_q = Queue<std::string>(length);

  if (length == 0)
    return 0;

  std::string tokens[] = {LN_TOKEN, SIN_TOKEN, COS_TOKEN, TAN_TOKEN};

  // temp_operand is the current operand token that we are reading from the
  // postfix.
  ld temp_operand = 0;

  // temp_decimal is the current operand token that we are reading from the
  // postfix. but only the decimal part in this separate variable.
  ld temp_decimal = 0;

  // This flag will indicate that we are reading the whole part of the number or
  // the decimals
  bool calculate_decimals = false;

  int token_index = 0;
  bool is_inserting_token = false;
  std::string inserting_token = "";

  for (int i = 0; postfix[i] != '\0'; i++) {
    int character = postfix[i];

    if (!is_inserting_token) {
      if (token_index == 0) {
        for (int i = 0; i < 4; i++) {
          if (character == tokens[i][token_index]) {
            tokens_q.enqueue(tokens[i]);

            if (tokens[i][token_index + 1] == '\0') {
              is_inserting_token = true;
              inserting_token = tokens[i];
              temp_decimal = 0;
              temp_operand = 0;
              token_index = 0;
              calculate_decimals = false;
            }
          }
        }
      } else {
        std::string current_token;

        bool match_found = false;

        while (!tokens_q.is_empty() && !match_found && !is_inserting_token) {
          tokens_q.dequeue(current_token);

          if (character == current_token[token_index]) {
            tokens_q.enqueue(current_token);

            if (current_token[token_index + 1] == '\0') {
              is_inserting_token = true;
              inserting_token = current_token;
              temp_decimal = 0;
              temp_operand = 0;
              token_index = 0;
              calculate_decimals = false;
            }

            match_found = true;
          }
        }
      }
    }

    if (!is_inserting_token) {
      if (!tokens_q.is_empty()) {
        token_index++;
      } else {
        while (token_index > 0) {
          i--;
          token_index--;
        }
      }
    }

    if (character == '.') {
      calculate_decimals = true;
      continue;
    }

    if (character == '!') {
      if (postfix[i - 1] >= '0' && postfix[i - 1] <= '9') {
        operands.push(factorial(temp_operand));

        temp_operand = 0;
        temp_decimal = 0;
        calculate_decimals = false;
      }
    }

    if (character >= '0' && character <= '9') {
      if (calculate_decimals) {
        temp_decimal = (character - '0') + temp_decimal * 10;
      } else {

        temp_operand = (character - '0') + temp_operand * 10;
      }

      continue;
    }

    if (character == SEPERATOR || (is_inserting_token && character == ')')) {
      if (postfix[i - 1] >= '0' && postfix[i - 1] <= '9') {
        // divide the decimal part until it reaches less than 1,
        // so it will become the main decimal part of the current number token
        // that we are reading.
        while (temp_decimal >= 1) {
          temp_decimal /= 10;
        }

        if (is_inserting_token) {
          ld token_res =
              eval_postfix_token(inserting_token, temp_operand + temp_decimal);

          operands.push(token_res);
        } else {
          operands.push(temp_operand + temp_decimal);
        }

        temp_operand = 0;
        temp_decimal = 0;
        calculate_decimals = false;
        is_inserting_token = false;
        token_index = 0;

        while (!tokens_q.is_empty()) {
          tokens_q.dequeue();
        }
      }

      continue;
    }

    switch (character) {
    case '+': {
      ld a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b + a);

      break;
    }

    case '-': {
      ld a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b - a);

      break;
    }

    case '*': {
      ld a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b * a);

      break;
    }

    case '/': {
      ld a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(b / a);

      break;
    }

    case '^': {
      ld a, b;
      operands.pop(a);
      operands.pop(b);

      operands.push(powl(b, a));

      break;
    }

    default:
      continue;
    }
  }

  return operands.pop_and_return();
}

ld eval_postfix_token(std::string token, ld operand) {

  bool is_ln = token.compare(LN_TOKEN) == 0 ? true : false;

  if (is_ln) {
    return logl(operand);
  }

  bool is_sin = token.compare(SIN_TOKEN) == 0 ? true : false;

  if (is_sin) {
    return sinl(operand);
  }

  bool is_cos = token.compare(COS_TOKEN) == 0 ? true : false;

  if (is_cos) {
    return cosl(operand);
  }

  bool is_tan = token.compare(TAN_TOKEN) == 0 ? true : false;

  if (is_tan) {
    return tanl(operand);
  }

  return 0;
}
