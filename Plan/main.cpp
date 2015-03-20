#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <ctime>
#include <utility>
#include <stack>
#include <iostream>

using namespace std;

ifstream fin("plan.in");
ofstream fout("plan.out");

const int NMAX = 260;

vector <int> Graph[NMAX], G[NMAX], Lowlink(NMAX), Deep(NMAX), ctc(NMAX), X , Y, Nodes[NMAX];
stack <int> Stack;
bitset <NMAX> in_Stack, inGrade, outGrade;
int n, m, deep, StrongConnections, inNum, outNum;

inline void get_min ( int &a, int b) {
    if( a > b)
        a = b;
}

inline void Make_Graph() {
    for(int i = 1 ; i <= n ; ++ i)
        for(vector<int> :: iterator it = Graph[i].begin(); it != Graph[i].end(); ++ it)
            if(ctc[i] != ctc[*it])
                G[ctc[i]].push_back(ctc[*it]),
                inGrade[ctc[*it]] = true,
                outGrade[ctc[i]] = true;
}

void Tarjan(int node) {
    Lowlink[node] = Deep[node] = ++deep;
    Stack.push(node);
    in_Stack[node] = true;
    for(vector<int> :: iterator it = Graph[node].begin() ; it != Graph[node].end(); ++ it)
        if( !Deep[*it] ) {
            Tarjan(*it);
            get_min(Lowlink[node], Lowlink[*it]);
        }
        else if( in_Stack[*it] )
            get_min(Lowlink[node], Lowlink[*it]);
    if( Lowlink[node] == Deep[node] ) {
        int nod;
        ++ StrongConnections;
        do{
            nod = Stack.top();
            Nodes[StrongConnections].push_back(nod);
            ctc[nod] = StrongConnections;
            Stack.pop();
            in_Stack[nod] = false;
        }while(nod != node);
    }
}

int main()
{
    fin >> n >> m ;
    for(int i = 1; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        Graph[x].push_back(y);
    }
    for(int i = 1; i <= n ; ++ i)
        if(!Deep[i])
            Tarjan(i);

    if( StrongConnections == 1 ) { ///one single strongly connected component
        fout << "0\n";
        return 0;
    }
    Make_Graph();
    for(int i = 1 ; i <= StrongConnections ; ++ i) {
        if(!inGrade[i]) {
            ++ inNum;
            X.push_back(i);
        }
        if(!outGrade[i]){
            ++ outNum;
            Y.push_back(i);
        }
    }
    fout << max(inNum, outNum) << "\n";
    if(X.size() <= Y.size()) {
        for(int j = 0; j < X.size() - 1 ; ++ j) {
            fout << Nodes[Y[j]][0] << " " << Nodes[X[j+1]][0] << "\n";
            cerr << Y[j] << ' ' << X[j + 1] << '\n';
        }
        for(int j = X.size() - 1 ; j < Y.size() ; ++ j) {
            fout << Nodes[Y[j]][0] << " " << Nodes[X[0]][0] << "\n";
            cerr << Y[j] << ' ' << X[0] << '\n';
        }
    }
    else {
        for(int j = 0 ; j < Y.size(); ++ j) {
            fout << Nodes[Y[j]][0] << " " << Nodes[X[j+1]][0] << "\n";
            cerr << Y[j] << ' ' << X[j + 1] << '\n';
        }
        fout << Nodes[Y[0]][0] << " " << Nodes[X[0]][0] << "\n";
            cerr << Y[0] << ' ' << X[0] << '\n';

        for(int j = Y.size() + 1 ; j < X.size() ; ++ j) {
            fout << Nodes[Y[0]][0] << " " << Nodes[X[j]][0] << "\n";
            cerr << Y[0] << ' ' << X[j] << '\n';
        }
    }
    return 0;
}
