#include <iostream>
#include <ostream>

void create_magic_square(int n, int **square);
void create_magic_square_odd_dim(int n, int **square);

int main() {
  int n;
  std::cout << "Enter the dimension of square: (must be an odd number) ";
  std::cin >> n;

  if (n % 2 == 0) {
    std::cout << "Must be an odd number" << std::endl;
    return 1;
  }

  int **square = new int *[n];

  for (int i = 0; i < n; i++) {
    square[i] = new int[n];
  }

  create_magic_square(n, square);

  std::cout << "Magic square is: " << std::endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << square[i][j] << " ";
    }

    std::cout << std::endl;
  }

  for (int i = 0; i < n; i++) {
    delete[] square[i];
  }

  delete[] square;

  return 0;
}

void create_magic_square(int n, int **square) {
  /*
   * The magic constant formula: n(n^2 + 1)/2
   */

  create_magic_square_odd_dim(n, square);
}

void create_magic_square_odd_dim(int n, int **square) {

  int i = n / 2;
  int j = n - 1;
  int current_number = 1;

  while (current_number <= n * n) {
    if (i < 0 && j >= n) {
      i = 0;
      j = n - 2;
    } else {
      if (i < 0) {
        i = n - 1;
      }

      if (j >= n) {
        j = 0;
      }
    }

    if (square[i][j] != 0) {
      i++;
      j -= 2;
      continue;
    }

    square[i--][j++] = current_number++;
  }
}
