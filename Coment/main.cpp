#include <fstream>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>
#include <list>

using namespace std;

const char infile[] = "coment.in";
const char outfile[] = "coment.out";

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
bool G[MAXN][MAXN];
list <int> cycle;
bitset <MAXN> Used;

inline int searchSuccesor(const int &last) {
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i] && G[last][i])
            return i;
    return 0;
}

inline int searchPredecessor(const int &first) {
    for(int i = 1 ; i <= N ; ++ i)
        if(!Used[i] && G[i][first])
            return i;
    return 0;
}

inline void buildElementaryRoad() {
    int x = 1;               ///Pornesc din nodul 1
    cycle.push_back(x);      ///il adaug la list ciclurilor
    Used[x] = true;          ///marchez ca vizitat
    /// exist la dreapta => adaugand noduri in colo =>
    do {
        x = searchSuccesor(cycle.back());
        if(x) {
            cycle.push_back(x);
            Used[x] = true;
        }
    } while(x);
    do {
        x = searchPredecessor(cycle.front());
        if(x) {
            cycle.push_front(x);
            Used[x] = true;
        }
    } while(x);
}

inline void insertTheRest() {
    for(int x = 2 ; x <= N ; ++ x) {
        if(Used[x])
            continue;
        list<int> :: iterator it;
        for(it = cycle.begin(); G[*it][x] ; ++ it);
        cycle.insert(it, x);
        Used[x] = true;
    }
}

int main() {
    /**
        Ciclu Hamitonian in Graf Turneu
    */
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &N);
    M = N * (N - 1) / 2;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x][y] = 1;
    }
    buildElementaryRoad();
    insertTheRest();
    for(list<int> :: iterator it = cycle.begin(); it != cycle.end() ; ++ it)
        printf("%d ", *it);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
