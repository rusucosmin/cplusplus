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

const char infile[] = "nums.in";
const char outfile[] = "nums.out";

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

bool type[MAXN];
pair<string, int> Word[MAXN];
int N, M, Words, K[MAXN], arb[MAXN << 2], where[MAXN], sortPos[MAXN];
bitset <MAXN> Used;

struct classComp {
    inline bool operator () (const pair<string, int> &a, const pair<string, int> &b) const {
        if(a.first.size() == b.first.size())
            return a.first < b.first;
        return a.first.size() < b.first.size();
    }
};

void Update(const int &Node, const int &st, const int &dr, const int &pos) {
    if(st == dr) {
        arb[Node] = 1;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos);
    else Update(2*Node + 1, mid + 1, dr, pos);
    arb[Node] = arb[2*Node] + arb[2*Node + 1];
}

int Query(const int &Node, const int &st, const int &dr, const int &k) {
    if(st == dr)
        return st;
    int mid = ((st + dr) >> 1);
    if(arb[2*Node] >= k)
        return Query(2*Node, st, mid, k);
    return Query(2*Node + 1, mid + 1, dr, k - arb[2*Node]);
}

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> type[i];
        if(type[i]) {
            fin >> Word[++ Words].first;
            Word[Words].second = i;
        }
        else fin >> K[i];
    }
    sort(Word + 1, Word + Words + 1, classComp());
    for(int i = 1 ; i <= Words ; ++ i) {
        if(Word[i].first == Word[i - 1].first)
            sortPos[Word[i].second] = sortPos[Word[i - 1].second];
        else sortPos[Word[i].second] = sortPos[Word[i - 1].second] + 1;
        where[sortPos[Word[i].second]] = i;
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(type[i]) {
            if(Used[sortPos[i]])
                continue;
            Used[sortPos[i]] = true;
            Update(1, 1, N, sortPos[i]);
        }
        else fout << Word[where[Query(1, 1, N, K[i])]].first << '\n';
    fin.close();
    fout.close();
    return 0;
}
