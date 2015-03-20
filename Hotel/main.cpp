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

string file = "hotel";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
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

struct node {
    int best;
    int left;
    int right;
    void update(const int &Value) {
        best = Value;
        left = Value;
        right = Value;
    }
};

int N, P;
node Aint[MAXN << 2];

inline void Build(int Node, int st, int dr) {
    Aint[Node].update(dr - st + 1);
    if(st == dr)
        return;
    int mid = (st + dr) >> 1;
    Build(Node << 1, st, mid);
    Build((Node << 1) + 1, mid + 1, dr);
}

inline void Update(int Node, int st, int dr, int a, int b, int op) {
    if(a <= st && dr <= b) { /// subinterval => umplem camerele, respectiv le golim
        Aint[Node].update((dr - st + 1)*op);
        return ;
    }
    int mid = (st + dr) >> 1;
    int fst = Node << 1;
    int fdr = fst + 1;
    if( Aint[Node].best == dr - st + 1) {
        Aint[fst].update(mid - st + 1);
        Aint[fdr].update(dr - mid);
    }
    if(Aint[Node].best == 0) {
        Aint[fst].update(0);
        Aint[fdr].update(0);
    }
    if( a <= mid )
        Update(fst, st, mid, a, b, op);
    if( mid < b )
        Update(fdr, mid + 1, dr, a, b, op);
    if(Aint[fst].left == mid - st + 1)
        Aint[Node].left = Aint[fst].left + Aint[fdr].left;
    else Aint[Node].left = Aint[fst].left;
    if(Aint[fdr].right == dr - mid)
        Aint[Node].right = Aint[fdr].right + Aint[fst].right;
    else
        Aint[Node].right = Aint[fdr].right;
    Aint[Node].best = max(max(Aint[fst].best, Aint[fdr].best), Aint[fst].right + Aint[fdr].left);
}

int main() {
    /*
        daca c are valoarea 1, atunci el va fi urmat (pe aceeasi linie) de alte 2 numere, i si M, reprezentand numarul primei camere distribuite grupului abia sosit si numarul de membri ai grupului
        daca c are valoarea 2, atunci el va fi urmat (pe aceeasi linie) de alte 2 numere, i si M, reprezentand numarul primei camere care va fi eliberata de grupul care tocmai pleaca, precum si numarul de membri ai grupului care paraseste hotelul
        daca c are valoarea 3, el nu va fi urmat de nici un alt numar pe linia respectiva; programul va trebui, insa, sa afiseze in fisierul de iesire lungimea maxima a unei secvente de camere libere numerotate consecutiv.
    */
    cin >> N >> P;
    Build(1, 1, N);
    for(int i = 1 ; i <= P ; ++ i) {
        short c;
        cin >> c;
        if(c == 3) {
            cout << Aint[1].best << '\n';
            continue;
        }
        /// c = 0 => bagam in camere
        /// c = 1 => eliberam camere
        int x, y;
        -- c;
        cin >> x >> y;
        Update(1, 1, N, x, x + y - 1, c);
    }
    cin.close();
    cout.close();
    return 0;
}
