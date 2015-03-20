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

Graph T1, T2;
vector <int> center1, center2;
int N;

inline void getCenter(Graph & G, vector <int> & center) {
    vector <int> deg(N), last, act;
    int cnt = 0;
    for(int i = 0 ; i < N ; ++ i) {
        deg[i] = G[i].size();
        if(deg[i] == 1) {
            act.push_back(i);
            ++ cnt;
        }
    }
    while(cnt < N) {
        last = act;
        vector <int>().swap(act);
        for(It it = last.begin(), fin = last.end(); it != fin ; ++ it) {
            int Node = *it;
            for(It n = G[Node].begin(), finnn = G[Node].end(); n != finnn ; ++ n) {
                if(-- deg[*n] == 1) {
                    act.push_back(*n);
                    ++ cnt;
                }
            }
        }
    }
    center = act;
}

inline string buildVectors(Graph &G, int Node, int father) {
    vector <string> v;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == father)
            continue;
        v.push_back(buildVectors(G, *it, Node));
    }
    sort(v.begin(), v.end());
    string s = "1";
    for(vector <string> :: iterator it = v.begin(), fin = v.end(); it != fin ; ++ it)
        s += *it;
    return s + "0";
}

inline bool Check(int Root1, int Root2) {
    return buildVectors(T1, Root1, Root1) == buildVectors(T2, Root2, Root2);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int T;
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        cin >> N;
        for(int i = 1 ; i < N ; ++ i) {
            int a, b;
            cin >> a >> b;
            -- a;
            -- b;
            T1[a].push_back(b);
            T1[b].push_back(a);
        }
        for(int i = 1 ; i < N ; ++ i) {
            int a, b;
            cin >> a >> b;
            -- a;
            -- b;
            T2[a].push_back(b);
            T2[b].push_back(a);
        }
        getCenter(T1, center1);
        getCenter(T2, center2);
        if(center1.size() != center2.size())
            cout << "NO\n";
        else {
            if(center1.size() == 1) {
                if(Check(center1[0], center2[0]))
                    cout << "YES\n";
                else cout << "No\n";
            } else {
                if(Check(center1[0], center2[0]) | Check(center1[0], center2[1]))
                    cout << "YES\n";
                    else cout << "NO\n";
            }
        }
        for(int i = 0 ; i < N ; ++ i) {
            vector <int> ().swap(T1[i]);
            vector <int> ().swap(T2[i]);
        }
    }
    fin.close();
    fout.close();
    return 0;
}
