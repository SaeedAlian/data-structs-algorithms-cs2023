class Stack {
 private:
  int top;
  int max_size;
  int* items;

 public:
  Stack(int size);
  bool is_empty();
  bool is_full();
  int get_top();
  void push(int item);
  void pop();
  void pop(int& item);
  int pop_and_return();
  void print();
  void reverse();
  ~Stack();
};