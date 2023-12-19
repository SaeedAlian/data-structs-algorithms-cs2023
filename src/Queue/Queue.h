#pragma once

template <class T> class Queue {
private:
  int front;
  int rear;
  int max_size;
  T *items;

public:
  Queue();
  Queue(int size);
  bool is_empty();
  bool is_full();
  T get_front();
  void enqueue(T item);
  void dequeue();
  void dequeue(T &item);
  T dequeue_and_return();
  void print();
  ~Queue();
};
