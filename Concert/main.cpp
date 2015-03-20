#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>

using namespace std;

const char infile[] = "concert.in";
const char outfile[] = "concert.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct artist {
    int A, B, P, D1, D2;
};

artist A[MAXN];
int N;
int dp[MAXN];

struct classComp {
    inline bool operator () (const artist &a, const artist &b) {
        return a.B < b.B || (a.B == b.B && a.A < b.A);
    }
};

inline int Profit(const int &index) {
    return (A[index].B - A[index].A) * A[index].P;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i].A >> A[i].B >> A[i].P >> A[i].D1 >> A[i].D2;
    sort(A + 1, A + N + 1, classComp());
    for(int i = 1 ; i <= N ; ++ i) {
        dp[i] = Profit(i);
        for(int j = 1 ; j < i ; ++ j) {
            if(A[j].B <= A[i].A)
                dp[i] = max(dp[i], dp[j] + Profit(i));
            else {
                int pi1 = dp[j] + (A[i].A - A[j].B) * A[j].P + (A[i].B - A[i].A) * A[i].P - A[j].D2;
                int pi2 = dp[j] + (A[i].B - A[j].B) * A[i].P - A[i].D1;
                dp[i] = max(dp[i], max(pi1, pi2));
            }
        }
    }
    fout << *max_element(dp + 1, dp + N + 1) << "\n";
    fin.close();
    fout.close();
    return 0;
}
