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

const int MAXN = 1005;
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
const inline void Get_min(int &a, const int b)    {
    if( a > b ) a = b;
}
const inline void Get_max(int &a, const int b)    {
    if( a < b ) a = b;
}

int b[MAXN], a[MAXN], N, K;

int main() {
    cin.sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
#endif
    cin >> N >> K;
    vector <pair<char, pair<int, int> > > Ans, v;
    for(int i = 1 ; i <= N ; ++i) {
        cin >> a[i];
        Ans.push_back(make_pair('-',make_pair(1,1)));
    }
    Ans.push_back(make_pair('-',make_pair(1,1)));
    for(b[1] = 1 ; b[1] <= 1000 ; ++ b[1]) {
        v.clear();
        int x = b[1];
        if(a[1] > x)
            v.push_back(make_pair('-',make_pair(1,a[1]-x)));
        else if(a[1]!=x)
            v.push_back(make_pair('+',make_pair(1,x-a[1])));
        for(int i = 2; i <= N; ++i) {
            int x = b[i-1] + K;
            if(a[i] > x)
                v.push_back(make_pair('-',make_pair(i,a[i]-x)));
            else if(a[i]!=x)
                v.push_back(make_pair('+',make_pair(i,x-a[i])));
            b[i] = x;
        }
        if(Ans.size() > v.size()) {
            swap(Ans, v);
        }
    }
    cout<<Ans.size()<<"\n";
    for(unsigned i = 0; i < Ans.size(); ++i)
        cout<<Ans[i].first<<" "<<Ans[i].second.first<<" "<<Ans[i].second.second<<"\n";
    return 0;
}
