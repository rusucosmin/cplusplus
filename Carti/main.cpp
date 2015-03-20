#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

const char infile[] = "carti.in";
const char outfile[] = "carti.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 20;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, K, T, v[MAXN], vis[(1 << MAXN)], dp[(1 << MAXN)];
string card;

/// 0 daca cartea nu e luata
/// 1 daca cartea e luata

int Memoization(int state) {
    if(vis[state])
        return dp[state];
    vis[state] = 1; dp[state] = 1;
    for(int i = 0 ; i < N ; ++ i)
        if( !(state & ( 1 << i ) ) ) { /// nu am luat cartea
            int smask = state;
            for(int j = i ; !(state & ( 1 << j)) && j - i < K && j < N && ( j == i || v[j] == v[j-1] + 1) ; ++ j) {
                smask |= ( 1 << j );
                dp[state] = min(dp[state], Memoization(smask));
            }
        }
    dp[state] ^= 1; /// daca e castigatoare => necastigatoare si viceversa
    return dp[state];
}

inline void Solve() {
    fin >> N >> K;
    for(int i = 0 ; i < N ; ++ i) {
        fin >> card;
        if(card.size() == 2) {
            v[i] = 10;
            continue;
        }
        if(isdigit(card[0])) {
            v[i] = card[0] - '0';
            continue;
        }
        switch(card[0]) {
        case 'A':
            v[i] = 1;
            break;
        case 'J':
            v[i] = 11;
            break;
        case 'Q':
            v[i] = 12;
            break;
        case 'K':
            v[i] = 13;
            break;
        }
    }
    sort(v, v + N);
    for(int i = 0 ; i <= ( 1 << N ) ; ++ i)
        dp[i] = vis[i] = 0;
    if(Memoization(0))
        fout << "Alice\n";
    else fout << "Bob\n";
}

int main() {
    for(fin >> T ; T ; -- T) {
        Solve();
    }
    fin.close();
    fout.close();
    return 0;
}
