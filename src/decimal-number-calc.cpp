#include <iostream>

#include "./DecimalNumber/DecimalNumber.h"

#define PRECISION 100
#define MAX_NUMBER_SIZE 1024 * 10

int main() {
  std::string num1;
  std::string num2;

  std::cout << "Enter first number : ";
  std::cin >> num1;

  std::cout << "Enter second number : ";
  std::cin >> num2;

  DecimalNumber decimal1 = DecimalNumber(num1, PRECISION);
  DecimalNumber decimal2 = DecimalNumber(num2, PRECISION);

  std::cout << "The sum of both is : ";

  DecimalNumber sum = decimal1.add(&decimal2);
  sum.print();

  std::cout << "The product of both is : ";

  DecimalNumber prod = decimal1.multiply(&decimal2);
  prod.print();

  return 0;
}
