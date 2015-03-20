#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "tribute.in";
const char outfile[] = "tribute.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

long long N, Dx, Dy, freqx[MAXN], freqy[MAXN], many[MAXN], st[MAXN], dr[MAXN], sus[MAXN], jos[MAXN];

int main() {
    fin >> N >> Dx >> Dy;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        fin >> x >> y;
        ++ freqx[x];  ++ freqy[y];
    }
    many[0] = freqx[0];
    for(int i = 1 ; i < MAXN ; ++ i) {
        st[i] = 1*many[i-1] + st[i-1];
        many[i] = many[i-1] + freqx[i];
    }
    for(int i = 0 ; i < MAXN ; ++ i)
        many[i] = 0;
    for(int i = MAXN - 1 ; i >= 0; -- i) {
        dr[i] = 1*many[i+1] + dr[i+1];
        many[i] = many[i+1] + freqx[i];
    }
    long long Ans1 = st[0] + dr[Dx];
    for(int i = 1 ; i < MAXN ; ++ i)
        if( i + Dx < MAXN)
            Ans1  = min(Ans1 , st[i] + dr[i + Dx]);
    for(int i = 0 ; i < MAXN ; ++ i)
        many[i] = 0;
    many[0] = freqy[0];
    for(int i = 1 ; i < MAXN ; ++ i) {
        jos[i] = 1*many[i-1] + jos[i-1];
        many[i] = many[i-1] + freqy[i];
    }
    for(int i = 0 ; i < MAXN ; ++ i)
        many[i] = 0;
    for(int i = MAXN - 1 ; i >= 0; -- i) {
        sus[i] = 1*many[i+1] + sus[i+1];
        many[i] = many[i+1] + freqy[i];
    }
    long long Ans2 = jos[0] + sus[Dy];
    for(int i = 1 ; i + Dy < MAXN ; ++ i)
        if( i + Dy < MAXN )
            Ans2 = min(Ans2, jos[i] + sus[i + Dy]);
    fout << Ans1 + Ans2;
    fin.close();
    fout.close();
    return 0;
}
