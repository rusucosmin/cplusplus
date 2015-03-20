/*#include <fstream>
#include <vector>
#include <bitset>
#include <list>
#include <algorithm>

using namespace std;

const char infile[] = "control.in";
const char outfile[] = "control.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 250005;
const int MAXM = 3000005;
const int MAXCTC = 7654;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) {
    if( a > b ) return b;
    return a;
}
const inline int max(const int &a, const int &b) {
    if( a < b ) return b;
    return a;
}
const inline void Get_min(int &a, const int b)   {
    if( a > b ) a = b;
}
const inline void Get_max(int &a, const int b)   {
    if( a < b ) a = b;
}

int N, nrc, deep;
int many[MAXN], G[MAXM], Level[MAXN], lowLink[MAXN], where[MAXN], howmany[MAXCTC], sol[MAXCTC];
list <int> st;
bitset <MAXN> inStack;
bitset <MAXCTC> Gt[MAXCTC], add[MAXCTC];

void Tarjan(const int &Node) {
    Level[Node] = lowLink[Node] = ++ deep;
    st.push_back(Node);
    inStack[Node] = true;
    for(int i = many[Node] ; i < many[Node+1] ; ++ i)
        if(!Level[G[i]]) {
            Tarjan(G[i]);
            lowLink[Node] = min(lowLink[Node], lowLink[G[i]]);
        } else if(inStack[G[i]])
                  lowLink[Node] = min(lowLink[Node], lowLink[G[i]]);
        if(Level[Node] == lowLink[Node]) {
            int nod;
            ++ nrc;
            do {
                nod = st.back();
                    ++ howmany[nrc];
                    where[nod] = nrc;
                    st.pop_back();
                    inStack[nod] = 0;
                } while(nod != Node);
            }
}

void buildCTC() {
    for(int i = 1 ; i <= N ; ++ i)
        if(!Level[i])
            Tarjan(i);
    for(int i = 1 ; i <= N ; ++ i)
        for(int j = many[i] ; j < many[i + 1] ; ++ j)
            if(where[i] != where[G[j]])
                Gt[i][G[j]] = 1;
    st.clear();
}

void DFs(const int &Node) {
    inStack[Node] = true;
    for(int i = 1 ; i <= nrc ; ++ i)
        if(!inStack[i] && Gt[Node][i])
            DFs(i);
    st.push_front(Node);
}

void Solve(const int &Node) {
    sol[Node] = 0;
    add[Node][Node] = 1;
    inStack[Node] = 1;
    for(int i = 1 ; i <= nrc ; ++ i)
        if(!inStack[i] && Gt[Node][i])
            Solve(i);
    for(int i = 1 ; i <= nrc; ++ i)
        if(Gt[Node][i])
            add[Node]|=add[i];
    for(int i = 1; i <= nrc; ++ i)
        if(add[Node][i])
            sol[Node] += howmany[i];
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int x, y;
        fin >> x;
        many[i + 1] = many[i] + x;
        for(int j = 0 ; j < x ; ++ j) {
            fin >> y;
            G[many[i] + j] = y;
        }
    }
    buildCTC();
    inStack.reset();
    for(int i = 1 ; i <= N ; ++ i)
        if(!inStack[i])
            DFs(i);
    inStack.reset();
    reverse(st.begin(), st.end());
    for(list<int> :: iterator it = st.begin(); it != st.end(); ++ it)
        if(!inStack[*it])
            Solve(*it);
    for(int i = 1 ; i <= N ; ++ i)
        fout << sol[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}*/

#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>

using namespace std;

ifstream cin("control.in");
ofstream cout("control.out");

const int MAXN = 100005;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
int N, Ans;
bitset<MAXN> Used;

inline void DFs(int Node, int Father) {
    Used[Node] = true;
    ++ Ans;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Used[*it])
            DFs(*it, Node);
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i){
        int x, y;
        for(cin >> x ; x ; -- x) {
            cin >> y;
            G[i].push_back(y);
        }
    }
    for(int i = 1 ; i <= N ; ++ i) {
        Used.reset();
        Ans = 0;
        DFs(i, i);
        cout << Ans << ' ';
    }
    cin.close();
    cout.close();
    return 0;
}
