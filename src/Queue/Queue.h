#pragma once

class Queue {
 private:
  int front;
  int rear;
  int max_size;
  int* items;

 public:
  Queue(int size);
  bool is_empty();
  bool is_full();
  int get_front();
  void enqueue(int item);
  void dequeue();
  void dequeue(int& item);
  int dequeue_and_return();
  void print();
  ~Queue();
};