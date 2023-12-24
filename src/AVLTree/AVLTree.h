#pragma once

#include "../Queue/Queue.h"

class AVLTree {
private:
  AVLTreeNode *root;

  int get_max_int(int a, int b);
  int get_node_height(AVLTreeNode *node);
  int get_balance_factor(AVLTreeNode *node);
  AVLTreeNode *left_rotation(AVLTreeNode *root);
  AVLTreeNode *right_rotation(AVLTreeNode *root);
  AVLTreeNode *find_inorder_successor(AVLTreeNode *node);

  AVLTreeNode *new_node(int key);

  AVLTreeNode *insert_node_helper(AVLTreeNode *node, int key);
  AVLTreeNode *remove_node_helper(AVLTreeNode *node, int key);
  AVLTreeNode *search_node_helper(AVLTreeNode *node, int key);

  void traverse_inorder_helper(AVLTreeNode *node);
  void traverse_postorder_helper(AVLTreeNode *node);

public:
  AVLTree();

  /*
   * Creates a node and adds it to the tree.
   * Returns 1 if it was successful, otherwise returns 0
   */
  int insert(int key);

  /*
   * Removes a node from the tree.
   * Returns 1 if it was successful, otherwise returns 0
   */
  int remove(int key);

  /*
   * Traverse the tree in inorder
   */
  void traverse_inorder();

  /*
   * Traverse the tree in postorder
   */
  void traverse_postorder();

  /*
   * Traverse the tree in level order
   */
  void traverse_level_order();

  /*
   * Searches for a key inside the tree.
   * Returns 1 if it was exists, otherwise returns 0
   */
  int search(int key);

  ~AVLTree();
};
