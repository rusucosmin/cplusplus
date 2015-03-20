#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "propozitie";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int MOD = 9001;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, K, A[MAXN], B[MAXN], Sum;
char S[MAXN];

const char voc[] = "aeiou";

int main() {
    cin >> N >> K >> (S+1);
    for(int i = 1 ; i <= N ; ++ i)
        if(strchr(voc, S[i]))
            A[i] = A[i-1] + 1;
            else A[i] = A[i-1];
    B[0] = 1;
    int j = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        Sum = (Sum + B[i-1]) % MOD;
        while(A[i] - A[j] > K)
            Sum -= B[j], ++ j;
        while(Sum < 0)
            Sum += 9001;
        B[i] = Sum;
    }
    cout << B[N] % MOD << '\n';
    cin.close();
    cout.close();
    return 0;
}
