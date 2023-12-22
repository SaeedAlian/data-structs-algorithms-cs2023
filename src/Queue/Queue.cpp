#include "./Queue.h"

#include <iostream>

#define DEFAULT_MAX_SIZE 1024 * 2

template <class T> Queue<T>::Queue() {
  front = -1;
  rear = -1;
  max_size = DEFAULT_MAX_SIZE;
  items = new T[DEFAULT_MAX_SIZE];
}

template <class T> Queue<T>::Queue(int size) {
  front = -1;
  rear = -1;
  max_size = size;
  items = new T[size];
}

template <class T> bool Queue<T>::is_empty() { return front == -1; }

template <class T> bool Queue<T>::is_full() {
  return (rear + 1) % max_size == front;
}

template <class T> T Queue<T>::get_front() { return items[front]; }

template <class T> void Queue<T>::enqueue(T item) {
  if (is_full()) {
    std::cout << "Queue is full!" << std::endl;
    std::cout << "Cannot add " << item << " into queue." << std::endl;
    return;
  }

  if (is_empty()) {
    front = (front + 1) % max_size;
  }

  rear = (rear + 1) % max_size;

  items[rear] = item;
}

template <class T> void Queue<T>::dequeue() {
  if (is_empty()) {
    std::cout << "Queue is empty!" << std::endl;
    std::cout << "Cannot remove item from queue." << std::endl;
    return;
  }

  if (front == rear) {
    front = rear = -1;
  } else {
    front = (front + 1) % max_size;
  }
}

template <class T> void Queue<T>::dequeue(T &item) {
  if (is_empty()) {
    std::cout << "Queue is empty!" << std::endl;
    std::cout << "Cannot remove item from queue." << std::endl;
    return;
  }

  int temp_front = front;

  if (front == rear) {
    front = rear = -1;
  } else {
    front = (front + 1) % max_size;
  }

  item = items[temp_front];
}

template <class T> void Queue<T>::print() {
  int temp_front = front;

  if (is_empty()) {
    std::cout << "Queue is empty!" << std::endl;
  } else {
    std::cout << "Queue items: " << std::endl;

    do {
      std::cout << items[temp_front] << " ";
      temp_front = (temp_front + 1) % max_size;
    } while (temp_front != (rear + 1) % max_size);
  }

  std::cout << std::endl;
}

template <class T> Queue<T>::~Queue() { delete[] items; }

template class Queue<char>;
template class Queue<int>;
template class Queue<std::string>;
template class Queue<float>;
template class Queue<double>;
template class Queue<TreeNode>;
template class Queue<TreeNode *>;
