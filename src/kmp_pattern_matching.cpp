#include <iostream>
#include <stdlib.h>
#include <string>

int *compute_lps(std::string pattern, int lp) {
  int len = 0;

  int *lps = new int[lp];

  lps[0] = 0;

  int i = 1;

  while (i < lp) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        i++;
      }
    }
  }

  return lps;
}

int kmp_matching(std::string string, std::string pattern) {
  int ls = string.length();
  int lp = pattern.length();

  int *lps = compute_lps(pattern, lp);

  int i = 0;
  int j = 0;

  while ((ls - i) >= (lp - j)) {
    if (string[i] == pattern[j]) {
      j++;
      i++;
    }

    if (j == lp) {
      free(lps);
      return i - j;
    } else if (i < ls && string[i] != pattern[j]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }

  delete[] lps;
  return -1;
}

int main() {
  std::string str = "abcabdddaabddabbgbacgda";
  std::string sub = "abddab";

  int match_index = kmp_matching(str, sub);

  std::cout << "Match index: " << match_index << std::endl;

  return 0;
}
