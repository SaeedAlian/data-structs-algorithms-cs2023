#include "./DecimalNumber.h"

#include <iostream>
#include <string>

int DecimalNumber::string_digit_to_int(char digit) { return (int)digit - 48; }

void DecimalNumber::separate_number(std::string number_string) {
  int start_decimal_index = 0;
  bool reached_decimal_point = false;
  whole_part = string_digit_to_int(number_string[0]);

  for (int i = 1; number_string[i] != '\0'; i++) {
    if ((int)number_string[i] == 46) {
      reached_decimal_point = true;
      start_decimal_index = i + 1;
      continue;
    }

    if (!reached_decimal_point) {
      int digit = string_digit_to_int(number_string[i]);
      whole_part = (whole_part * 10) + digit;
    } else {
      int current_index = i - start_decimal_index;
      if (current_index > precision - 1)
        break;

      decimals[current_index] = string_digit_to_int(number_string[i]);
    }
  }
}

DecimalNumber::DecimalNumber(std::string number_string, int number_precision) {
  // ! Verify the input.

  precision = number_precision;
  decimals = new int[number_precision];
  separate_number(number_string);
}

DecimalNumber::DecimalNumber(int number_whole_part, int *number_decimals,
                             int number_precision) {
  whole_part = number_whole_part;
  precision = number_precision;
  decimals = new int[number_precision];

  for (int i = 0; i < precision; i++) {
    decimals[i] = number_decimals[i];
  }
}

DecimalNumber::~DecimalNumber() { delete[] decimals; }

DecimalNumber DecimalNumber::add(DecimalNumber *other) {
  int *other_number_decimals = other->get_decimals();
  int other_number_precision = other->get_precision();

  int new_precision =
      other_number_precision > precision ? other_number_precision : precision;

  int new_whole_part = other->get_whole_part() + whole_part;

  int *new_decimals = new int[new_precision];

  for (int i = 0; i < precision; i++) {
    new_decimals[i] = decimals[i];
  }

  for (int i = other_number_precision - 1; i >= 0; i--) {
    int sum = new_decimals[i] + other_number_decimals[i];

    if (sum > 9) {
      if (i == 0) {
        new_whole_part++;
      } else {
        new_decimals[i - 1]++;
      }

      new_decimals[i] = sum % 10;
    } else {
      new_decimals[i] = sum;
    }
  }

  DecimalNumber new_number =
      DecimalNumber(new_whole_part, new_decimals, new_precision);

  delete[] new_decimals;

  return new_number;
}

DecimalNumber DecimalNumber::multiply(DecimalNumber *other) {
  int *other_number_decimals = other->get_decimals();
  int other_number_precision = other->get_precision();
  int other_number_whole_part = other->get_whole_part();

  int new_whole_part = whole_part * other_number_whole_part;

  int new_precision = precision + other_number_precision;

  int *new_decimals = new int[new_precision];

  // Product of this decimals with other's decimals
  for (int i = precision - 1; i >= 0; i--) {
    for (int j = other_number_precision - 1; j >= 0; j--) {
      int current_decimal_index = i + j + 1;

      int product = decimals[i] * other_number_decimals[j];

      int answer = product % 10;
      int carry = product / 10;

      new_decimals[current_decimal_index] += answer;

      if (current_decimal_index == 0) {
        new_whole_part += carry;
      } else {
        new_decimals[current_decimal_index - 1] += carry;
      }

      if (new_decimals[current_decimal_index] > 9) {
        if (current_decimal_index == 0) {
          new_whole_part++;
        } else {
          new_decimals[current_decimal_index - 1] +=
              new_decimals[current_decimal_index] / 10;
        }

        new_decimals[current_decimal_index] =
            new_decimals[current_decimal_index] % 10;
      }
    }
  }

  // Product of this whole part with other's decimals
  int this_whole_part_temp = whole_part;
  int whole_part_power = 0;

  while (this_whole_part_temp > 0) {
    int last_digit_of_whole_part = this_whole_part_temp % 10;

    for (int i = other_number_precision - 1; i >= 0; i--) {
      int current_decimal_index = i - whole_part_power;

      int product = other_number_decimals[i] * last_digit_of_whole_part;

      if (current_decimal_index < 0) {
        new_whole_part += product;
        continue;
      }

      int answer = product % 10;
      int carry = product / 10;

      new_decimals[current_decimal_index] += answer;

      if (current_decimal_index <= 0) {
        new_whole_part += carry;
      } else {
        new_decimals[i - 1] += carry;
      }

      if (new_decimals[current_decimal_index] > 9) {
        if (current_decimal_index <= 0) {
          new_whole_part++;
        } else {
          new_decimals[current_decimal_index - 1] +=
              new_decimals[current_decimal_index] / 10;
        }

        new_decimals[current_decimal_index] =
            new_decimals[current_decimal_index] % 10;
      }
    }

    whole_part_power++;
    this_whole_part_temp /= 10;
  }

  // Product of other's whole part with this decimals
  int other_whole_part_temp = other_number_whole_part;
  whole_part_power = 0;

  while (other_whole_part_temp > 0) {
    int last_digit_of_whole_part = other_whole_part_temp % 10;

    for (int i = precision - 1; i >= 0; i--) {
      int current_decimal_index = i - whole_part_power;

      int product = decimals[i] * last_digit_of_whole_part;

      if (current_decimal_index < 0) {
        new_whole_part += product;
        continue;
      }

      int answer = product % 10;
      int carry = product / 10;

      new_decimals[current_decimal_index] += answer;

      if (current_decimal_index <= 0) {
        new_whole_part += carry;
      } else {
        new_decimals[i - 1] += carry;
      }

      if (new_decimals[current_decimal_index] > 9) {
        if (current_decimal_index <= 0) {
          new_whole_part++;
        } else {
          new_decimals[current_decimal_index - 1] +=
              new_decimals[current_decimal_index] / 10;
        }

        new_decimals[current_decimal_index] =
            new_decimals[current_decimal_index] % 10;
      }
    }

    whole_part_power++;
    other_whole_part_temp /= 10;
  }

  DecimalNumber new_number =
      DecimalNumber(new_whole_part, new_decimals, new_precision);

  delete[] new_decimals;

  return new_number;
}

int DecimalNumber::get_precision() { return precision; }

int DecimalNumber::get_whole_part() { return whole_part; }

int *DecimalNumber::get_decimals() { return decimals; }

void DecimalNumber::print() {
  std::cout << "Number : " << whole_part << ".";

  for (int i = 0; i < precision; i++) {
    std::cout << decimals[i];
  }

  std::cout << std::endl;
}
