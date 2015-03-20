#include <fstream>
#include <vector>
#include <bitset>
#include <stack>
 
using namespace std;
 
const char infile[] = "secv6.in";
const char outfile[] = "secv6.out";
 
ifstream fin(infile);
ofstream fout(outfile);
 
const int MAXN = 4005;
const int MOD = 8192;
const int oo = 0x3f3f3f3f;
 
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
 
const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }
 
long long Ans;
 
int main() {
    int N;
    fin >> N;
    int M = min(N, MOD);
    vector <int> v(M);
    for(int i = 0 ; i < M ; ++ i)
        fin >> v[i];
    stack <long long> St;
    for(int i = 0 ; i < N ; ++ i) {
        long long a = 1LL * i + (1LL * v[i / MOD] ^ v[i % MOD]);
        while(!St.empty() && St.top() < a) {
            St.pop();
            ++ Ans;
        }
        if(!St.empty())
            ++ Ans;
        while(!St.empty() && St.top() == a)
            St.pop();
        St.push(a);
    }
    fout << Ans << "\n";
    fin.close();
    fout.close();
    return 0;
}
