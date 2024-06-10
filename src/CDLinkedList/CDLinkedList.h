#pragma once

struct CDLLNode {
  int key;
  CDLLNode *next;
  CDLLNode *prev;
};

class CDLinkedList {
private:
  CDLLNode *head;
  CDLLNode *tail;

public:
  CDLinkedList();
  CDLLNode *search(int key);
  CDLLNode *push(int key);
  CDLLNode *push_at(CDLLNode *at_node, int key);
  CDLLNode *append(int key);
  void pop();
  void unshift();
  void remove(CDLLNode *node);
  void print();
  ~CDLinkedList();
};
