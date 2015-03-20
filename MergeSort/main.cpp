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
#include <iostream>

using namespace std;

string file = "algsort";

ifstream fin( (file + ".in").c_str() );
ofstream fout( (file + ".out").c_str() );

const int MAXN = 500005;
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

int N, A[MAXN], B[MAXN];

inline void mergeSort(int l, int r) {
    if(l >= r)
        return;
    int m = (l + r) >> 1;
    mergeSort(l, m);
    mergeSort(m+1, r);

    int i = l, j = m + 1;
    int k = l - 1;
    while(i <= m && j <= r) {
        if(A[i] <= A[j]) {
            B[++ k] = A[i];
            ++ i;
        } else {
            B[++ k] = A[j];
            ++ j;
        }
    }
    while(i <= m) {
        B[++ k] = A[i];
        ++ i;
    }
    while(j <= r) {
        B[++ k] = A[j];
        ++ j;
    }
    for(int i = l ; i <= r ; ++ i)
        A[i] = B[i];
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        fin >> A[i];
    mergeSort(1, N);
    for(int i = 1; i <= N ; ++ i)
        fout << A[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
