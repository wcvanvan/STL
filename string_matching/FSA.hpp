#include <string.h>
#define total_chars 256
#define trans_func(i, j) (trans_func[(i) * (m) + (j)])

void transition(int* trans_func, char* pattern, int m);

int FSA(char* pattern, char* text) {
    int m = strlen(pattern);
    int n = strlen(text);
    int* trans_func = new int[total_chars * m];
    transition(trans_func, pattern, m);
    int q = 0;
    for (int i = 0; i < n; i++) {
        q = trans_func(text[i], q);
        if (q == m) {
            return i - m + 1;
        }
    }
    return -1;
}

void transition(int* trans_func, char* pattern, int m) {
    for (int i = 0; i < total_chars; i++) {
        if (i == pattern[0]) {
            trans_func(i, 0) = 1;
        }
        else {
            trans_func(i, 0) = 0;
        }
    }
    int X = 0;
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < total_chars; i++) {
            if (pattern[j] == i) {
                trans_func(i, j) = j + 1;
            }
            else {
                trans_func(i, j) = trans_func(i, X);
            }
        }
        X = trans_func(pattern[j], X);
    }
}