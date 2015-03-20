#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "prefixe.in";
const char outfile[] = "prefixe.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 131080;
const int oo = 0x3f3f3f3f;

int Z, pi[MAXN];

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    fin >> Z;
    while(Z --) {
        string s;
        fin >> s;
        pi[0] = -1;
        int K = -1;
        fout << 0 << ' ';
        for(int i = 1 ; i < s.size() ; ++ i) {
            while(K != -1 && s[i] != s[K + 1])
                K = pi[K];
            if(s[i] == s[K + 1])
                ++ K;
            pi[i] = K;
            fout << K + 1 << ' ';
        }
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
