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

string file = "rps";

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

struct Trie {
    int Nr;
    int Best;
    Trie *v[3];
    Trie() {
        Nr = Best = 0;
        for(int i = 0 ; i < 3 ; ++ i)
            v[i] = NULL;
    };
};

int N, K, W, D;
string s;
Trie Root;

inline int maxSon(const Trie &Node, int hand, int beaten) {
    int Ans = 0;
    if(Node.v[hand] != NULL)
        Ans += Node.v[hand]->Best;
    if(Node.v[beaten] != NULL)
        Ans += W * Node.v[beaten]->Nr;
    return Ans;
}

void Insert(Trie &Node, int Level) {
    if(Level == K) {
        ++ Node.Nr;
        Node.Best = D * Node.Nr;
        return;
    }
    /// Adaug R, P, sau S in functie de ce caracter am pe pozitia Level
    int Son;
    switch(s[Level]) {
    case 'R':
        Son = 0;
        break;
    case 'P':
        Son = 1;
        break;
    case 'S':
        Son = 2;
        break;
    }
    if(Node.v[Son] == NULL)
        Node.v[Son] = new Trie;
    /// Inserez urmatoarea pozitia -> fiul ales
    Insert(*Node.v[Son], Level + 1);
    ++ Node.Nr;
    ///Calculez efectiv dinamica
    Node.Best = maxSon(Node, 0, 2);
    Get_max(Node.Best, maxSon(Node, 1, 0));
    Get_max(Node.Best, maxSon(Node, 2, 1));
}

inline void Query(Trie &Node, int Level) {
    if(Level == K)
        return;
    int Move = 1;
    int Best = maxSon(Node, 1, 0);
    int actBest = maxSon(Node, 0, 2);
    if(Best < actBest) {
        Best = actBest;
        Move = 0;
    }
    actBest = maxSon(Node, 2, 1);
    if(Best < actBest) {
        Best = actBest;
        Move = 2;
    }
    switch(Move) {
    case 0:
        cout << 'R';
        break;
    case 1:
        cout << 'P';
        break;
    case 2:
        cout << 'S';
        break;
    }
    if(Node.v[Move])
        Query(*Node.v[Move], Level+1);
    else
        for( ; Level < K - 1 ; ++ Level)
            cout << 'P';
}

int main() {
    cin >> N >> K >> W >> D;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> s;
        Insert(Root, 0);
        Query(Root, 0);
        cout << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
