#include "./Stack.h"

#include <iostream>

#define DEFAULT_MAX_SIZE 1024 * 2

template <class T> Stack<T>::Stack() {
  top = -1;
  max_size = DEFAULT_MAX_SIZE;
  items = new T[DEFAULT_MAX_SIZE];
}

template <class T> Stack<T>::Stack(int size) {
  top = -1;
  max_size = size;
  items = new T[size];
}

template <class T> bool Stack<T>::is_empty() { return top == -1; }

template <class T> bool Stack<T>::is_full() { return top == max_size - 1; }

template <class T> T Stack<T>::get_top() { return items[top]; }

template <class T> void Stack<T>::push(T item) {
  if (is_full()) {
    std::cout << "Stack is full!" << std::endl;
    std::cout << "Cannot add " << item << " into stack." << std::endl;
    return;
  }

  items[++top] = item;
}

template <class T> void Stack<T>::pop() {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return;
  }

  top--;
}

template <class T> void Stack<T>::pop(T &item) {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return;
  }

  item = items[top--];
}

template <class T> T Stack<T>::pop_and_return() {
  if (is_empty()) {
    std::cout << "Stack is empty!" << std::endl;
    std::cout << "Cannot remove item from stack." << std::endl;
    return (T)0;
  }

  return items[top--];
}

template <class T> void Stack<T>::print() {
  std::cout << "Stack items :" << std::endl;

  int top = top;

  while (top > -1) {
    std::cout << "   "
              << "item " << top << ": " << items[top] << std::endl;

    top--;
  }
}

template <class T> void Stack<T>::reverse() {
  for (int i = 0; i <= top / 2; i++) {
    T temp = items[top - i];
    items[top - i] = items[i];
    items[i] = temp;
  }
}

template <class T> Stack<T>::~Stack() { delete[] items; }

template class Stack<char>;
template class Stack<int>;
template class Stack<std::string>;
template class Stack<float>;
template class Stack<double>;
