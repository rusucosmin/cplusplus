#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "curatenie.in";
const char outfile[] = "curatenie.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 500005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct node{
    int idx;
    node * _left;
    node * _right;
    node(const int &value) {
        idx = value;
        _left = _right = 0;
    }
};

int N, M, poz[MAXN], inordine[MAXN], postordine[MAXN], fii[MAXN][2];

void solve(const int &st, const int &dr, node * & nod) {
    if(st > dr)
        return;
    int mid = poz[postordine[++ M]];
    nod = new node(inordine[mid]);
    solve(st, mid - 1, nod -> _left);
    solve(mid + 1, dr, nod -> _right);
    if(nod -> _left)
    fii[inordine[mid]][0] = nod -> _left -> idx;
    if(nod -> _right)
    fii[inordine[mid]][1] = nod -> _right -> idx;
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> inordine[i];
        poz[inordine[i]] = i;
    }
    for(int i = 1 ; i <= N ; ++ i)
        fin >> postordine[i];
    node *root;// = new node(postordine[1]);
    solve(1, N, root);
    for(int i = 1 ; i <= N ; ++ i)
        fout << fii[i][0] << ' ' << fii[i][1] << '\n';
    fin.close();
    fout.close();
    return 0;
}
