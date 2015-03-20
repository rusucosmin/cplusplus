#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "gminmax.in";
const char outfile[] = "gminmax.out";

//ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, deg[MAXN], Nodes, Ans, solNodes, arb[MAXN * 3];
bitset <MAXN> Used;
Graph G;

void Update(const int &Node, const int &st, const int &dr, const int &pos, const int &value) {
    if(st == dr) {
        arb[Node] = value;
        return ;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    if(deg[arb[2*Node]] >= deg[arb[2*Node + 1]])
        arb[Node] = arb[2*Node + 1];
    else arb[Node] = arb[2*Node];
}

class Scanner {
  public:
    Scanner(string file, int buffer_size = 32768):
            buffer_size_(buffer_size) {
        file_ = fopen(file.c_str(), "r");
        buffer_ = new char[buffer_size];
        pointer_ = buffer_ + buffer_size_;
    }

    Scanner& operator>>(int &object) {
        object = 0;
        while (next() < '0' or next() > '9')
            advance();
        while (next() >= '0' and next() <= '9') {
            object = object * 10 + next() - '0';
            advance();
        }
        return *this;
    }

  private:
    char next() {
        if (pointer_ == buffer_ + buffer_size_) {
            pointer_ = buffer_;
            fread(buffer_, 1, buffer_size_, file_);
        }
        return *pointer_;
    }

    void advance() {
        ++pointer_;
    }

    FILE *file_;
    int buffer_size_;
    char *buffer_, *pointer_;
};
Scanner fin(infile);

void Build(const int &Node, const int &st, const int &dr) {
    if(st == dr) {
        arb[Node] = st;
        return ;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid);
    Build(2*Node + 1, mid + 1, dr);
    if(deg[arb[2*Node]] >= deg[arb[2*Node + 1]])
        arb[Node] = arb[2*Node + 1];
    else arb[Node] = arb[2*Node];
}

int main() {
    fin >> N >> M;
    Nodes = N;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        fin >> x >> y;
        ++ deg[x];
        ++ deg[y];
        G[x].push_back(y);
        G[y].push_back(x);
    }
    Build(1, 1, N);
    deg[0] = oo;
    Ans = deg[arb[1]];
    solNodes = N;
    while(Nodes -- ) {
        int minNode = arb[1];
        Used[minNode] = true;
        if(deg[minNode] > Ans) {
            Ans = deg[minNode];
            solNodes = Nodes + 1;
        }
        if(Ans >= Nodes) {
            break;
        }
        Update(1, 1, N, minNode, 0);
        for(It it = G[minNode].begin(), fin = G[minNode].end(); it != fin ; ++ it)
            if(!Used[*it]) {
                -- deg[*it];
                Update(1, 1, N, *it, *it);
            }
    }
    fout << Ans << ' ' << solNodes << '\n';
//    fin.close();
    fout.close();
    return 0;
}
