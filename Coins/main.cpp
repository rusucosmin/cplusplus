#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string.h>

using namespace std;

const char infile[] = "coins.in";
const char outfile[] = "coins.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 22;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

char a[1 << MAXN];
int s[MAXN];
int Ans, N;

inline void InitDynamic() {
    memset(a, -1, sizeof(a));
    for(int i = 1 ; i <= MAXN ; ++ i)
        a[(1 << i)-1] = 1;
}

bool memoization(int mask) { /// player 0 = paftemie
    if(a[mask] != -1)  return a[mask];
    int first = -1;
    int ret = 1;
    for(int i = 0 ; i < 22 ; ++ i)
        if(mask & ( 1 << i )) { /// am bitul 1
            if(first != -1) {
                int state = mask ^ ( 1 << i ) | ( 1 << first );
                ret &= memoization(state);
            }
        }
        else first = i;
    ret ^= 1;
    a[mask] = ret;
    return ret;
}

int main() {
    InitDynamic();
    for(fin >> N; N ; -- N) {
        int mask = 0, coins = 0;
        for(int i = MAXN - 1 ; i >= 0 ; -- i)
            fin >> s[i];
        for(int i = 0; i < 22 ; ++ i) {
            mask <<= 1;
            if(s[i])
                mask |= 1,
                ++ coins;
        }
        if(memoization(mask))
            Ans += coins;
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
