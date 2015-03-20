#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "baruri.in";
const char outfile[] = "baruri.out";

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

int T, A[MAXN], S[MAXN];
int N, M;

class aib
{

private:
    long long a[MAXN];
public :
    inline int lsb(int x)
    {
        return (x^(x-1))&x;
    }
    void update(int where, int value)
    {
        while(where <= N)
        {
            a[where] += 1LL*value;
            where += lsb(where);
        }
    }
    long long query(int where)
    {
        long long sum = 0;
        while(where > 0)
        {
            sum += a[where];
            where -= lsb(where);
        }
        return sum;
    }
    void clear() {
        memset(a, 0, sizeof(a));
    }
};

aib arb;


int main() {
    fin >> T;
    for(int test = 1 ;test <= T ; ++ test) {
        fin >> N;
        arb.clear();
        for(int i = 1 ; i <= N ; ++ i) {
            fin >> A[i];
            arb.update(i, A[i]);
        }
        fin >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int op, b, d, b1, b2, x;
            fin >> op;
            if(op == 0) {
                long long Ans1 = 0, Ans2 = 0;
                fin >> b >> d;
                Ans1 = arb.query(min(N , b + d));
                Ans2 =  arb.query(max(1, b - d) - 1);
                fout << Ans1 - Ans2 - A[b] << '\n';
            } else if(op == 1) {
                fin >> x >> b;
                A[b] += x;
                arb.update(b, x);
            } else if(op == 2) {
                fin >> x >> b;
                A[b] -= x;
                arb.update(b, -x);

            } else if(op == 3) {
                fin >> x >> b1 >> b2;
                A[b1] -= x;
                A[b2] += x;
                arb.update(b1, -x);
                arb.update(b2, x);
            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
