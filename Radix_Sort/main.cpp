#define debug
#ifdef debug

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
#include <cosmin.h>

using namespace std;

const char infile[] = "radixsort.in";
const char outfile[] = "radixsort.out";

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

const int DIGIT = 8;
const int maxBucket = (1 << 8); /// 2 ^ 8 = 256
const int maxTimes = 32 / 8;
const int mask = (1 << 8) - 1;

inline void radixSort(vector <int> &v, int N) {
    vector <int> aux(N);
    for(int times = 0, sh = 0; times < maxTimes ; ++ times, sh += DIGIT) {
        vector <int> _count(maxBucket, 0);
        for(It it = v.begin(), fin = v.end(); it != fin ; ++ it)
            ++ _count[((*it >> sh) & mask)];
        for(int i = 1 ; i < maxBucket ; ++ i)
            _count[i] += _count[i - 1];
        for(auto it = v.rbegin(), fin = v.rend(); it != fin ; ++ it) {
            //cerr << ((*it >> sh )& mask) << _count[((*it >> sh) & mask)] - 1 << '\n';
            aux[ -- _count[((*it >> sh) & mask)] ] = *it;
        }
        swap(aux, v);
    }
}

int main() {
    int N, A, B, C;
    vector <int> v;
    fin >> N >> A >> B >> C;
    //cerr << N << ' ' << A << ' ' << B << ' ' << C << '\n';
    v.push_back(B);
    for(int i = 2 ; i <= N ; ++ i)
        v.push_back((1LL * A * v.back() + B) % C);//, cerr << v[i - 1] << ' ';
    radixSort(v, N);
    for(int i = 0 ; i < N ; i += 10)
        fout << v[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}

#else
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

const char infile[] = "radixsort.in";
const char outfile[] = "radixsort.out";

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

const int DIGIT = 8;
const int maxBucket = (1 << 8); /// 2 ^ 8 = 256
const int maxTimes = 32 / 8;
const int mask = (1 << 8) - 1;

vector <int> G[maxBucket];

inline void radixSort(vector <int> &v, int N) {
    vector <int> aux;
    for(int times = 0, sh = 0; times < maxTimes ; ++ times, sh += DIGIT) {
        for(It it = v.begin(), fin = v.end(); it != fin ; ++ it)
            G[((*it >> sh) & mask)].push_back(*it);
        for(int i = 0 ; i < maxBucket ; ++ i) {
            for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
                aux.push_back(*it);
            vector <int> ().swap(G[i]);
        }
        swap(aux, v);
        vector <int>().swap(aux);
    }
}

int main() {
    int N, A, B, C;
    vector <int> v;
    fin >> N >> A >> B >> C;
    v.push_back(B);
    for(int i = 2 ; i <= N ; ++ i)
        v.push_back((1LL * A * v.back() + B) % C);///, cerr << v[i - 1] << ' ';
    radixSort(v, N);
    for(int i = 0 ; i < N ; i += 10)
        fout << v[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}

#endif
