template <class T> class Stack {
private:
  int top;
  int max_size;
  T *items;

public:
  Stack();
  Stack(int size);
  bool is_empty();
  bool is_full();
  T get_top();
  void push(T item);
  void pop();
  void pop(T &item);
  T pop_and_return();
  void print();
  void reverse();
  ~Stack();
};
