#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "curcubeu.in";
const char outfile[] = "curcubeu.out";

const int MAXN = 1000105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A[MAXN], B[MAXN], C[MAXN], nxt[MAXN], Color[MAXN];

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d %d", &N, &A[1], &B[1], &C[1]);
    for(int i = 2 ; i < N ; ++ i) {
        A[i] = (1LL * A[i - 1] * i) % N;
        B[i] = (1LL * B[i - 1] * i) % N;
        C[i] = (1LL * C[i - 1] * i) % N;
    }
    for(int i = 1 ; i < N ; ++ i)
        nxt[i] = i;
    for(int j = N - 1 ; j >= 1 ; -- j) {
        if(A[j] > B[j])
            swap(A[j], B[j]);
        for(int i = A[j] ; i <= B[j] ; ++ i)
            if(!Color[i]) {
                Color[i] = C[j];
                nxt[i] = B[j] + 1;
            }
            else i = nxt[i] - 1;
    }
    for(int i = 1 ; i < N ; ++ i)
        printf("%d\n", Color[i]);
    return 0;
}
