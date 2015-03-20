#include <fstream>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <queue>

using namespace std;

const char infile[] = "telefon2.in";
const char outfile[] = "telefon2.out";

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
int vec[MAXN], init[MAXN];
queue <int> Q;
bitset <MAXN> notleaf, used;

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        scanf("%d", &x);
        vec[i] = x;
        init[i] = x;
        notleaf[x] = true;
    }
    int nrfrunze = 0, nrcicluri = 0, inceput = 0, sfarsit = 0;
    for (int frunza = 1 ; frunza <= N ; ++ frunza)
        if(!notleaf[frunza] && !used[frunza]) {
            ++ nrfrunze;
            int Node = frunza;
            used[Node] = true;
            while(!used[vec[Node]]) {
                used[vec[Node]] = true;
                Node = vec[Node];
            }
            if(!inceput)
                inceput = Node;
            if(!sfarsit)
                sfarsit = Node;
            vec[Node] = inceput;
            inceput = frunza;
        }

    for(int stNode = 1 ; stNode <= N ; ++ stNode)
        if(!used[stNode]) {
            ++ nrcicluri;
            int Node = stNode;
            used[Node] = true;
            while(!used[vec[Node]]) {
                used[vec[Node]] = true;
                Node = vec[Node];
            }
            if(!inceput)
                inceput = Node;
            if(!sfarsit)
                sfarsit = Node;
            vec[Node] = inceput;
            inceput = stNode;
        }
    vec[sfarsit] = inceput;
    int nrModificari = nrfrunze + nrcicluri;
    printf("%d\n", nrModificari);
    for(int i = 1 ; i <= N ; ++ i)
        if(vec[i] != init[i])
            printf("%d %d\n", i, vec[i]);
    return 0;
}
