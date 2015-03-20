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

const char infile[] = "simetrii.in";
const char outfile[] = "simetrii.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
pair<int, int> A[MAXN], B[MAXN], C[MAXN];

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i].first >> A[i].second;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> B[i].first >> B[i].second;
    sort(B + 1, B + N + 1);
    for(int j = 0 ; j < 4 ; ++ j) {
        for(int i = 1 ; i <= N ; ++ i)
            C[i] = A[i];
        sort(C + 1, C + N + 1);
        int Dx = B[1].first - C[1].first;
        int Dy = B[1].second - C[1].second;
        for(int i = 1 ; i <= N ; ++ i) {
            C[i].first += Dx;
            C[i].second += Dy;
        }
        sort(C + 1, C + N + 1);
        bool ok = true;
        for(int i = 1 ; i <= N ; ++ i)
            if(C[i] != B[i])
                ok = false;
        if(ok) {
            fout << "2\n1 0 0 " << j * 90 << '\n';
            fout << "0 " << Dx << ' ' << Dy << '\n';
            return 0;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            pair<int, int> newP = make_pair(-A[i].second, A[i].first);
            A[i] = newP;
        }
    }
    fout << "-1\n";
    fin.close();
    fout.close();
    return 0;
}
