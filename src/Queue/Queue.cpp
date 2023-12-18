#include "./Queue.h"

#include <iostream>

Queue::Queue(int size) {
  front = -1;
  rear = -1;
  max_size = size;
  items = new int[size];
}

bool Queue::is_empty() {
  return front == -1;
}

bool Queue::is_full() {
  return (rear + 1) % max_size == front;
}

int Queue::get_front() {
  return items[front];
}

void Queue::enqueue(int item) {
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

void Queue::dequeue() {
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

void Queue::dequeue(int& item) {
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

int Queue::dequeue_and_return() {
  if (is_empty()) {
    std::cout << "Queue is empty!" << std::endl;
    std::cout << "Cannot remove item from queue." << std::endl;
    return -1;
  }

  int temp_front = front;

  if (front == rear) {
    front = rear = -1;
  } else {
    front = (front + 1) % max_size;
  }

  return items[temp_front];
}

void Queue::print() {
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

Queue::~Queue() {
  delete[] items;
}