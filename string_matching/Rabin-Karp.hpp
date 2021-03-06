#include <string>

#define d ((256) % q)
using std::string;

/*
return the place of the first occurrence of pattern in text
*/
int Rabin_Karp(const string &pattern, const string &text, int q) {
    size_t m = pattern.length();
    size_t n = text.length();
    int p_hash = 0, t_hash = 0, c = 1;
    for (int i = 0; i < m; i++) {
        // calculate the hash value of pattern and the hash value of the first section of text
        p_hash = ((p_hash * d) % q + (pattern[i] % q)) % q;
        t_hash = ((t_hash * d) % q + (text[i] % q)) % q;
    }
    for (int i = 0; i < m - 1; i++) {
        // avoid having a too large number
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
        // use last section's hash value of text to calculate the next one
        t_hash = (d * (t_hash - text[i] * c) + text[i + m]) % q;
        if (t_hash < 0) {
            t_hash += q;
        }
    }
    return -1;
}