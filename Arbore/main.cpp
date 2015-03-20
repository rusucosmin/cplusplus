/*
    ONI 2000 :
    ARBORE
*/
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
#include <iomanip>

using namespace std;

string file = "arbore";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 105;
const int MAXP = 1005;
const int oo = 0x3f3f3f3f;

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

int N, K, Father[MAXN], V[MAXN];
Graph G;
set<int> Hash[MAXN];
bitset<MAXP> Sum[MAXN];
bitset<MAXN> isFather;
/**
    	Pentru Cj de la 1 la Numarul de elemente din lista lui J
	Pentru Ci de la 1 la Numarul de elemente din lista lui I,
	Daca (List[j,Cj]+List[i,Ci] nu a fost marcat in tabelul lui
	I) se marcheaza si se adauga la sfarsitul listei lui I (dar
    nu se actualizeaza inca numarul de elemente ale lui I).

*/
inline void DFs() {
    for(int i = 1 ; i <= N ; ++ i) {
        for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
            for(set<int> :: iterator Cj = Hash[*it].begin() ; Cj !=  Hash[*it].end(); ++ Cj)
                for(set<int> :: iterator Ci = Hash[i].begin(); Ci != Hash[i].end(); ++ Ci)
                    if(!Sum[i][*Cj + *Ci])
                        Hash[i].insert(*Cj + *Ci), Sum[i][*Cj + *Ci] = true;
    }
}

int main() {
    cin >> N >> K;
    cin >> V[1];
    isFather[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        cin >> Father[i] >> V[i];
        G[Father[i]].push_back(i);
        isFather[Father[i]] = true;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!isFather[i])
            Sum[i][V[i]] = true, Hash[i].insert(V[i]);
    DFs();
    for(int i = 1 ; i <= N ; ++ i)
        if(Sum[i][K])
            cout << i << '\n';
    cin.close();
    cout.close();
    return 0;
}
