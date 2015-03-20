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
#include <unordered_map>
#include <sstream>

using namespace std;

const char infile[] = "litere2.in";
const char outfile[] = "litere2.out";

ofstream fout(outfile);

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char s[MAXN];
vector <pair<int, int> > S;
bitset <1 << 26> used;
int ans, N;

inline void afis(int pos) {
    while(pos < N && isalpha(s[pos])) {
        fout << s[pos];
        ++ pos;
    }
}

int main() {
    freopen(infile, "r", stdin);
    fgets(s, MAXN, stdin);
    N = strlen(s);
    cerr << N << '\n';

    for(int i = 0 ; i < N ;) {
        while(!isalpha(s[i]))
            ++ i;
        if(i >= N)
            break;
        int cod = 0;
        int index = -1;
        while(isalpha(s[i])) {
            if(index == -1)
                index = i;
            cod |= (1 << (s[i] - 'a'));
            ++ i;
        }
        if(index == -1)
            continue;
        S.push_back(make_pair(cod, index));
        if(!used[cod])
            ++ ans;
        used[cod] = 1;
    }
    fout << ans << '\n';
    sort(S.begin(), S.end());
    for(int i = 0 ; i < S.size() ; ++ i) {
        ///cerr << S[i].first << ' ' << S[i].second << '\n';
        while(i + 1 < S.size() && S[i].first == S[i + 1].first) {
            afis(S[i].second);
            fout << ' ';
            ++ i;
        }
        afis(S[i].second);
        fout << '\n';
    }
    return 0;
}
