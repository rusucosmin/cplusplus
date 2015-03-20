#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <string.h>
#include <stack>
#include <iterator>

using namespace std;

ifstream cin("strazi.in");
ofstream cout("strazi.out");


const int MAXN = 505;
const int oo = (1<<31)-1;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

Graph G;
vector<int> Idx(MAXN), LowLink(MAXN), SComp(MAXN);
stack <int> Stack;
bitset <MAXN> inStack;
int N, M, StrConnComp, deep;

inline void Get_min(int &a, int b) {
    if(a > b)
        a = b;
}

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
    if(LowLink[Node] == Idx[Node]) {
        int Nod;
        ++ StrConnComp;
        do {
            SComp[Nod = Stack.top()] = StrConnComp;
            Stack.pop();
            inStack[Nod] = false;
        } while(Nod != Node);
    }
}

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!Idx[i])
            Tarjan(i);
    cout << StrConnComp << "\n";
    if(StrConnComp == 1)
        cout << "DA\n";
    else {
        cout << "NU\n";
        // TODO (Cosmin Rusu#9#): Pornesc o parcurgere din Nodul 1 si vad din care nu se ajunge, si din toti in
        // nodul 1 folosind graful transpus
    }
    cin.close();
    cout.close();
    return 0;
}
