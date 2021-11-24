#include <string>
#define total_chars 256
#define trans_func(i, j) (trans_func[(i) * (m) + (j)])

using std::string;

void transition(int* trans_func, string pattern);

int FSA(const string& pattern, const string &text) {
  size_t m = pattern.length();
  size_t n = text.length();
  int* trans_func = new int[total_chars * m];
  transition(trans_func, pattern);
  int q = 0;
  for (int i = 0; i < n; i++) {
    q = trans_func(text[i], q);
    if (q == m) {
      return int(i - m + 1);
    }
  }
  return -1;
}

void transition(int* trans_func, string pattern) {
  size_t m = pattern.length();
  for (int i = 0; i < total_chars; i++) {
    if (i == pattern[0]) {
      trans_func(i, 0) = 1;
    } else {
      trans_func(i, 0) = 0;
    }
  }
  int X = 0;
  for (int j = 1; j < m; j++) {
    for (int i = 0; i < total_chars; i++) {
      if (pattern[j] == i) {
        trans_func(i, j) = j + 1;
      } else {
        trans_func(i, j) = trans_func(i, X);
      }
    }
    X = trans_func(pattern[j], X);
  }
}