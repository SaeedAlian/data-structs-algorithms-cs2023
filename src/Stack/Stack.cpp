#include "./Stack.h"

#include <iostream>

Stack::Stack(int size) {
  top = -1;
  max_size = size;
  items = new int[size];
}

bool Stack::is_empty() {
  return top == -1;
}

bool Stack::is_full() {
  return top == max_size - 1;
}

int Stack::get_top() {
  return items[top];
}

void Stack::push(int item) {
  if (is_full()) {
    std::cout << "Stack is full!" << std::endl;
    std::cout << "Cannot add " << item << " into stack." << std::endl;
    return;
  }

  items[++top] = item;
}

void Stack::pop() {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return;
  }

  top--;
}

void Stack::pop(int& item) {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return;
  }

  item = items[top--];
}

int Stack::pop_and_return() {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return -1;
  }

  return items[top--];
}

void Stack::print() {
  std::cout << "Stack items :" << std::endl;

  int top = top;

  while (top > -1) {
    std::cout << "   "
              << "item " << top << ": " << items[top] << std::endl;

    top--;
  }
}

void Stack::reverse() {
  for (int i = 0; i <= top / 2; i++) {
    int temp = items[top - i];
    items[top - i] = items[i];
    items[i] = temp;
  }
}

Stack::~Stack() {
  delete[] items;
}