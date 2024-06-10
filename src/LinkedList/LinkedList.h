#pragma once

struct LLNode {
  int key;
  LLNode *next;
};

class LinkedList {
private:
  LLNode *head;

public:
  LinkedList();
  LLNode *search(int key);
  void push(int key);
  void pop();
  void print();
  ~LinkedList();
};
