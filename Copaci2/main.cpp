#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "copaci2.in";
const char outfile[] = "copaci2.out";

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

int N, H[MAXN], K, C[MAXN], A[MAXN][MAXN], Ans;

inline int myAbs(const int &Value) {
    if(Value > 0)
        return Value;
    return -Value;
}

inline int Check(int value) {
    int ret = oo;
    memset(A, oo, sizeof(A));
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= H[i] ; ++ j) {
            int mini = oo;
            for(int k = max(0, j - value) ; k <= min(H[i-1], j + value) ; ++k)
                mini = min(mini, A[i-1][k]);
            A[i][j] = mini + myAbs(H[i] - j)*C[i];
            if(i == N)
                ret = min(ret, A[i][j]);
        }
    }
    for(int i = 1 ; i <= H[N] ; ++ i)
        fout << A[N][i] << ' ';
    fout << "\n";
    return ret;
}

void binarySearch() {
    int li = 1, ls = 1000;
    while(li <= ls) {
        int mid = (li + ls) / 2;
        if(Check(mid) <= K){
            li = mid + 1;
            Ans = mid;
        }
        else ls = mid - 1;
    }
}

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> H[i] >> C[i];
    binarySearch();
    fout << Ans << ' ' << Check(Ans) << '\n';
    fin.close();
    fout.close();
    return 0;
}
