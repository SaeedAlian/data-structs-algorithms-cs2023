#pragma once

#include "../Queue/Queue.h"

class BinaryTree {
private:
  TreeNode *root;
  void remove_deepest_node(TreeNode *node);

public:
  BinaryTree();

  /*
   * Creates a node and adds it to the tree.
   * Returns 1 if it was successful, otherwise returns 0
   */
  int add(int key);

  /*
   * Removes a node from the tree.
   * Returns 1 if it was successful, otherwise returns 0
   */
  int remove(int key);

  /*
   * Traverse the tree in level order
   */
  void traverse();

  ~BinaryTree();
};
