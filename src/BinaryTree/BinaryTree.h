#pragma once

#include "../Queue/Queue.h"

class BinaryTree {
private:
  TreeNode *root;
  void remove_deepest_node(TreeNode *node);

public:
  BinaryTree();
  int add(int key);
  int remove(int key);
  void traverse();
  ~BinaryTree();
};
