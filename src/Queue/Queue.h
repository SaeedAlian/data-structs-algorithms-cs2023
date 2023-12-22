#pragma once

#include <ostream>

struct TreeNode {
  int key;
  TreeNode *right_child;
  TreeNode *left_child;

  friend std::ostream &operator<<(std::ostream &os, const TreeNode &node) {
    os << node.key;
    return os;
  }
};

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
  void print();
  ~Queue();
};
