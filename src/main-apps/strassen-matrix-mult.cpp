#include <iostream>
#include <vector>

#define MAX_SIZE 256

std::vector<std::vector<int>>
add_matrix(const std::vector<std::vector<int>> &A,
           const std::vector<std::vector<int>> &B);

std::vector<std::vector<int>>
subtract_matrix(const std::vector<std::vector<int>> &A,
                const std::vector<std::vector<int>> &B);

std::vector<std::vector<int>>
mult_matrix(const std::vector<std::vector<int>> &A,
            const std::vector<std::vector<int>> &B);

std::vector<std::vector<int>>
naive_mult_matrix(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B);

void print_matrix(const std::vector<std::vector<int>> A);

int main() {
  std::vector<std::vector<int>> A = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {1, 3, 6, 8}, {12, 3, 2, 1}};
  std::vector<std::vector<int>> B = {
      {5, 1, 8, 2}, {4, 12, 4, 13}, {-2, 0, 0, 3}, {12, -1, 0, 0}};

  std::vector<std::vector<int>> strassen_result = mult_matrix(A, B);
  std::vector<std::vector<int>> naive_result = naive_mult_matrix(A, B);

  std::cout << "Strassen : " << std::endl;
  print_matrix(strassen_result);
  std::cout << std::endl;

  std::cout << "Naive : " << std::endl;
  print_matrix(naive_result);
  std::cout << std::endl;

  return 0;
}

std::vector<std::vector<int>>
add_matrix(const std::vector<std::vector<int>> &A,
           const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = A[i][j] + B[i][j];
    }
  }

  return result;
}

std::vector<std::vector<int>>
subtract_matrix(const std::vector<std::vector<int>> &A,
                const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = A[i][j] - B[i][j];
    }
  }

  return result;
}

std::vector<std::vector<int>>
mult_matrix(const std::vector<std::vector<int>> &A,
            const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  if (n == 1) {
    result[0][0] = A[0][0] * B[0][0];
    return result;
  }

  int new_size = n / 2;

  std::vector<std::vector<int>> A11(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> A12(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> A21(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> A22(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> B11(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> B12(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> B21(new_size, std::vector<int>(new_size, 0));
  std::vector<std::vector<int>> B22(new_size, std::vector<int>(new_size, 0));

  // Divide input matrices into 4 submatrices
  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + new_size];
      A21[i][j] = A[i + new_size][j];
      A22[i][j] = A[i + new_size][j + new_size];

      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + new_size];
      B21[i][j] = B[i + new_size][j];
      B22[i][j] = B[i + new_size][j + new_size];
    }
  }

  // P1 = (A11 + A22) * (B11 + B22)
  std::vector<std::vector<int>> P1 =
      mult_matrix(add_matrix(A11, A22), add_matrix(B11, B22));

  // P2 = (A21 + A22) * B11
  std::vector<std::vector<int>> P2 = mult_matrix(add_matrix(A21, A22), B11);

  // P3 = A11 * (B12 - B22)
  std::vector<std::vector<int>> P3 =
      mult_matrix(A11, subtract_matrix(B12, B22));

  // P4 = A22 * (B21 - B11)
  std::vector<std::vector<int>> P4 =
      mult_matrix(A22, subtract_matrix(B21, B11));

  // P5 = (A11 + A12) * B22
  std::vector<std::vector<int>> P5 = mult_matrix(add_matrix(A11, A12), B22);

  // P6 = (A21 - A11) * (B11 + B12)
  std::vector<std::vector<int>> P6 =
      mult_matrix(subtract_matrix(A21, A11), add_matrix(B11, B12));

  // P7 = (A12 - A22) * (B21 + B22)
  std::vector<std::vector<int>> P7 =
      mult_matrix(subtract_matrix(A12, A22), add_matrix(B21, B22));

  // result11 = ((P1 + P4) - P5) + P7
  std::vector<std::vector<int>> result11 =
      add_matrix(subtract_matrix(add_matrix(P1, P4), P5), P7);

  // result12 = P3 + P5
  std::vector<std::vector<int>> result12 = add_matrix(P3, P5);

  // result21 = P2 + P4
  std::vector<std::vector<int>> result21 = add_matrix(P2, P4);

  // result22 = ((P1 + P3) - P2) + P6
  std::vector<std::vector<int>> result22 =
      add_matrix(add_matrix(subtract_matrix(P1, P2), P3), P6);

  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      result[i][j] = result11[i][j];
      result[i][j + new_size] = result12[i][j];
      result[i + new_size][j] = result21[i][j];
      result[i + new_size][j + new_size] = result22[i][j];
    }
  }

  return result;
}

std::vector<std::vector<int>>
naive_mult_matrix(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = 0;
      for (int k = 0; k < n; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

void print_matrix(const std::vector<std::vector<int>> A) {
  int n = A.size();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << A[i][j] << "  ";
    }

    std::cout << std::endl;
  }
}
