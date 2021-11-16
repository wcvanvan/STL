#include <string>
using std::string;
void find_next(string pattern, int* next);

int KMP(string pattern, string text) {
  int m = pattern.length();
  int n = text.length();
  int* next = new int[m];
  for (int i = 0; i < m; i++) {
    next[i] = 0;
  }
  find_next(pattern, next);
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && text[i] != pattern[j]) {
      j = next[j - 1];
    }
    if (text[i] == pattern[j]) {
      j++;
    }
    if (j == m) {
      return i - m + 1;
    }
  }
  return -1;
}

void find_next(string pattern, int* next) {
  int m = pattern.length();
  int head = 0;
  next[0] = 0;
  for (int tail = 1; tail < m; tail++) {
    while (head > 0 && pattern[head] != pattern[tail]) {
      head = next[head - 1];
    }
    if (pattern[head] == pattern[tail]) {
      head++;
    }
    next[tail] += head;
  }
}