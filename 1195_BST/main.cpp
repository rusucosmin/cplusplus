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

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, x[MAXN];
vector <int> in, post, pre;

struct node {
    int value;
    node *st, *dr;
    node(const int & _value) {
        value = _value;
        st = 0;
        dr = 0;
    }
};

void Insert(const int &Value, node *Node) {
    if(Value < Node -> value) {
        if(Node -> st)
            Insert(Value, Node -> st);
        else Node -> st = new node(Value);
    }
    else {
        if(Node -> dr)
            Insert(Value, Node -> dr);
        else Node -> dr = new node(Value);
    }
}

void DFs(const node *Node) {
    /// pre = node, st , dr
    /// in = st node dr
    /// post = st dr node
    pre.push_back(Node -> value);
    if(Node -> st)
        DFs(Node->st);
    in.push_back(Node -> value);
    if(Node -> dr)
        DFs(Node->dr);
    post.push_back(Node -> value);
}

#define fin cin
#define fout cout

int main() {
    cin.sync_with_stdio(false);
    fin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        int N;
        fin >> N;
        fin >> x[1];
        node *root = new node(x[1]);
        for(int i = 2 ; i <= N ; ++ i) {
            fin >> x[i];
            Insert(x[i], root);
        }
        pre.clear();
        in.clear();
        post.clear();
        DFs(root);
        fout << "Case " << test << ":\n";
        fout << "Pre.:";
        for(int i = 0 ; i < pre.size() ; ++ i)
            fout << ' ' << pre[i];
        fout << '\n';
        fout << "In..:";
        for(int i = 0 ; i < in.size() ; ++ i)
            fout << ' ' << in[i];
        fout << '\n';
        fout << "Post:";
        for(int i = 0 ; i < post.size() ; ++ i)
            fout << ' ' << post[i];
            fout << "\n\n";
    }
    return 0;
}
