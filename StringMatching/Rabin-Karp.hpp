#include <cmath>
#include <cstring>
#define d ((256) % q)

/*
return the place of the first occurrence of pattern in text
*/
int Rabin_Karp(char *pattern, char *text, int q) {
  int m = strlen(pattern);
  int n = strlen(text);
  int p_hash = 0, t_hash = 0, c = 1;
  for (int i = 0; i < m; i++) {
    p_hash = ((p_hash * d) % q + (pattern[i] % q)) % q;
    t_hash = ((t_hash * d) % q + (text[i] % q)) % q;
  }
  for (int i = 0; i < m - 1; i++) {
    c = (c * d) % q;
  }
  for (int i = 0; i <= n - m; i++) {
    if (p_hash == t_hash) {
      bool isIdentical = false;
      for (int j = 0; j < m; j++) {
        if (pattern[j] != text[i + j]) {
          break;
        }
        if (j == m - 1) {
          isIdentical = true;
        }
      }
      if (isIdentical) {
        return i;
      }
    }
    t_hash = (d * (t_hash - text[i] * c) + text[i + m]) % q;
    if (t_hash < 0) {
      t_hash += q;
    }
  }
  return -1;
}