#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int maxn = 2000005;
const int mod1 = 666013;
const int mod2 = 100007;
const int base = 73;

char a[maxn], b[maxn];
int n, m;
int pattern_hash1, pattern_hash2;
int text_hash1, text_hash2;

int main() {
    fin.getline(a + 1, maxn);
    fin.getline(b + 1, maxn);

    n = strlen(a + 1);
    m = strlen(b + 1);

    if(n > m) {
        fout << "0\n";
        return 0;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        pattern_hash1 = (pattern_hash1 * base + a[i]) % mod1;
        pattern_hash2 = (pattern_hash2 * base + a[i]) % mod2;
    }
    int power = 1, power2 = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        text_hash1 = (text_hash1 * base + b[i]) % mod1;
        power = (power * base) % mod1;
        text_hash2 = (text_hash2 * base + b[i]) % mod2;
        power2 = (power2 * base) % mod2;
    }
    vector <int> matches;
    if(text_hash1 == pattern_hash1 && text_hash2 == pattern_hash2)
        matches.push_back(0);
    for(int i = n + 1 ; i <= m ; ++ i) {
        text_hash1 = (text_hash1 * base + b[i]) % mod1;
        text_hash1 = (text_hash1 - (power * b[i - n]) % mod1 + mod1) % mod1;
        text_hash2 = (text_hash2 * base + b[i]) % mod2;
        text_hash2 = (text_hash2 - (power2 * b[i - n]) % mod2 + mod2) % mod2;
        if(pattern_hash1 == text_hash1 && pattern_hash2 == text_hash2)
            matches.push_back(i - n);
    }
    fout << matches.size() << '\n';
    for(int i = 0 ; i < min((int)(1000), (int)(matches.size())) ; ++ i)
        fout << matches[i] << ' ';
}
