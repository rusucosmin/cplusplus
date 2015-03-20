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

using namespace std;

ifstream cin("plimbare.in");
ofstream cout("plimbare.out");

const int MAXN = 101;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G, Gt;
int N, Idx[MAXN], LowLink[MAXN], deep, Maxi, Root, CycleLength;
bool ret;
vector<int> A, B, C, D;
stack<int> Stack;
bitset<MAXN> inStack, Best, Used, inCycle;
map<int, int> PCycle;

inline void Tarjan(int Node) {
    Idx[Node] = LowLink[Node] = ++ deep;
    Stack.push(Node);
    inStack[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin ; ++ it)
        if(!Idx[*it]) {
            Tarjan(*it);
            Get_min(LowLink[Node], LowLink[*it]);
        }
        else if(inStack[*it])
            Get_min(LowLink[Node], LowLink[*it]);
    if(Idx[Node] == LowLink[Node]) {
        set<int> Component;
        bitset<MAXN>act;
        int nod;
        do {
            Component.insert(nod = Stack.top());
            act[nod] = true;
            Stack.pop();
            inStack[Node] = false;
        } while(nod != Node);
        if(Maxi < Component.size())
            Maxi = Component.size() , Root = *(Component.begin()), Best = act;
    }
}

inline void DFs(int Node, int Father) {
    if(ret)
        return;
    Used[Node] = true;
    for(It it = G[Node].begin(), fin = G[Node].end() ; it != fin && !ret ; ++ it)
        if(Best[*it]) {
            if(*it == Father)
                continue;
            if(!Used[*it]){
                inCycle[*it] = true;
                PCycle[Node] = *it;
                DFs(*it, Node);
            }
            else {
                PCycle[Node] = *it;
                ret = true;
                return;
            }
        }
}

int main() {
    cin >> N;
    for(int i = 1 ; i <= (N*(N-1))/2 ; ++ i){
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Idx[i])
            Tarjan(i);
    inCycle[Root] = true;
    DFs(Root, 0);
    cout << PCycle.size() + B.size() + min(C.size(), D.size()) << "\n";
    while(B.size()) {
        int pair_root = PCycle[Root];
        PCycle[Root] = B.back();
        PCycle[B.back()] = pair_root;
        B.pop_back();
    }
    while(C.size() && D.size()) {
        int pair_root = PCycle[Root];
        PCycle[Root] = C.back();
        PCycle[C.back()] = D.back();
        PCycle[D.back()] = pair_root;
        C.pop_back();
        D.pop_back();
    }
    cout << Root << " ";
    int TR = Root;
    do {
        TR = PCycle[TR];
        cout << TR << " ";
    }while(PCycle[TR] != Root);
    cin.close();
    cout.close();
    return 0;
}
