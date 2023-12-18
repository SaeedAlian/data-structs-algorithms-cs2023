#include <string>

#pragma once

class DecimalNumber {
 private:
  int whole_part;
  int* decimals;
  int precision;

  int string_digit_to_int(char digit);
  void separate_number(std::string number);

 public:
  DecimalNumber(std::string number, int precision);
  DecimalNumber(int whole_part, int* decimals, int precision);
  ~DecimalNumber();
  DecimalNumber add(DecimalNumber* other);
  DecimalNumber multiply(DecimalNumber* other);
  int get_precision();
  int get_whole_part();
  int* get_decimals();
  void print();
};
