#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "revolutie.in";
const char outfile[] = "revolutie.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 130;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, pereche[MAXN], cuplaj[MAXN];
bitset <MAXN> M[MAXN], Used, Afisat;

bool pairUp(const int &Node) {
    if(Used[Node])
        return false;
    Used[Node] = true;
    for(int i = 1 ; i <= N ; ++ i)
        if(M[Node][i])
            if(!pereche[i] || pairUp(pereche[i])) {
                pereche[i] = Node;
                cuplaj[Node] = i;
                return true;
            }
    return false;
}

inline void maximumMatching() {
    int matching = 0;
    for(bool change = true ; change ; ) {
        change = false;
        Used.reset();
        for(int i = 1 ; i <= N ; ++ i)
            if(!cuplaj[i] && pairUp(i)) {
                change = true;
                ++ matching;
            }
    }
    if(matching != N) {
        fout << "-1\n";
        return;
    }
    fout << N << '\n';
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j)
            if(cuplaj[j] == i) {
                fout << "L " << i << ' ' << j << '\n';
                swap(cuplaj[i], cuplaj[j]);
            }
}

int main() {
    /// Construiesc un graf bipartit pe baza matricei de adiacenta din input
    /// exista solutie daca exista un cuplaj maxim de cardinalitate N
    /// astfel ca voi interschimba linia i cu cu coloana cuplaj[i]
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = 1 ; j <= N ; ++ j){
            bool x;
            fin >> x;
            M[i][j] = x;
        }
    maximumMatching();
    fin.close();
    fout.close();
    return 0;
}
