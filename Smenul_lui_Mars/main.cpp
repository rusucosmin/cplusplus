#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "mars.in";
const char outfile[] = "mars.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A[MAXN], B[MAXN], M;

int main() {
    fin >> N >> M;
    //for(int i = 1 ; i <= N ; ++ i)
    //    fin >> A[i], B[i] = B[i - 1] + A[i];
    for(int i = 1 ; i <= M ; ++ i) {
        int st, dr, x;
        fin >> st >> dr >> x;
        B[st] += x;
        B[dr + 1] -= x;
    }
    memset(A, 0, sizeof(A));
    A[0] = B[0];
    for(int i = 1 ; i <= N ; ++ i)
        A[i] = A[i - 1] + B[i], fout << A[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
