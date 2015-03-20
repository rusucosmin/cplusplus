#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "sireturi.in";
const char outfile[] = "sireturi.out";

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

int T;

inline long long nrDivizori(const int &Value) {
    long long ret = 0;
    for(int i = 1 ; i <= Value ; ++ i)
        if(Value % i == 0)
            ++ ret;
    return ret;
}

int main() {
    fin >> T;
    for(int i = 1 ;i <= T; ++ i) {
        long long x;
        fin >> x;
        fout << nrDivizori(x * (x-1) / 2) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
