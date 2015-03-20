#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "jstc.in";
const char outfile[] = "jstc.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 1000010;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int A, B, st[MAXN], viz[MAXN], top, k, Father[10*MAXN], now;
char s[10*MAXN];

int Find(int Node) {
    int a = Node, b;
    while(!viz[a])
        a = Father[a + 1];
    while(!viz[Node] && a) {
        b = Father[Node + 1];
        Father[Node] = a;
        Node = b;
    }
    if(!a)
        return -1;
    return a;
}

int main() {
    long long sum = 0;
    fin >> A >> B;
    fin.get();
    fin.getline(s, 10*MAXN);
    int sz = strlen(s);
    for(int i = 1 ; i <= strlen(s) + 1 ; ++ i)
        Father[i] = sz + 1;
    for(int i = 0 ; i < sz ; ++ i) {
        char op = s[i];
        if(op == 'I') {
            st[++ top] = ++ k;
            viz[k] = 1;
            Father[k] = k;
        }
        if(op == 'E') {
            viz[st[top]] = 0;
            --top;
        }
        if(op == 'Q') {
            now = (1LL * A * now + B) % k + 1;
            if(st[top] < now) {
                -- sum;
                continue;
            }
            sum += 1LL * Find(now);
        }
    }
    fout << sum << '\n';
    fin.close();
    fout.close();
    return 0;
}
