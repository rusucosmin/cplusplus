#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "bleach.in";
const char outfile[] = "bleach.out";

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

int main() {
    priority_queue <long long, vector<long long>, greater<long long> > Q;
    long long N, K;
    fin >> N >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        long long x;
        fin >> x;
        Q.push(x);
    }
    long long A = 0;
    long long add = 0;
    ///  A = puterea de acum;
    for(long long i = K + 1 ; i <= N ; ++ i) {
        long long x;
        fin >> x;
        Q.push(x);
        long long B = Q.top();
        if(A >= B)
            A += B;
        else {
            add += (B - A);
            A = 2 * B;
        }
        Q.pop();
    }
    while(!Q.empty()) {
        long long B = Q.top();
        if(A >= B)
            A += B;
        else {
            add += (B - A);
            A = 2 * B;
        }
        Q.pop();
    }
    fout << add << '\n';
    fin.close();
    fout.close();
    return 0;
}
