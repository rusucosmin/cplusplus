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
#include <cassert>

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

const int dx[] = {-1,-1, 0, 1, 1, 1, 0,-1};
const int dy[] = { 0, 1, 1, 1, 0,-1,-1,-1};

class FiniteAutomaton {
public:
    struct Node {
        map<char, Node*> sons; /// TODO MODIFY SO THAT IT Won;t be a map, but a vector
        Node *fail;
        vector <int> where;
        Node() {
            fail = NULL;
        }
    };
    FiniteAutomaton() {
        Root = new Node();
    }
    inline void addString(Node *n, const string &s, const int &pos, const int &i) {
        if(s.size() == pos) {
            n->where.push_back(i);
            ans.push_back(make_pair(-1, make_pair(-1, -1)));
            return;
        }
        if(!n->sons[s[pos]])
            n->sons[s[pos]] = new Node();
        addString(n->sons[s[pos]], s, pos + 1, i);
    }
    inline Node *getRoot() {
        return Root;
    }
    inline void BuildFails() {
        Root->fail = Root;
        queue <Node*> Q;
        Q.push(Root);
        Node *n, *K;
        for( ; ! Q.empty() ; ) {
            n = Q.front();
            Q.pop();
            for(map<char, Node*> :: iterator it = n->sons.begin(); it != n->sons.end(); ++ it) {
                K = n->fail;
                while(K != Root && !K -> sons[it->first])
                    K = K->fail;
                if(K->sons[it->first] && K->sons[it->first] != it->second)
                    K = K->sons[it->first];
                it->second->fail = K;
                Q.push(it->second);
            }
        }
    }
    inline void AhoCorasick(const vector<string> &v, int x, int y, int dir, const int &N, const int &M) {
        Node *K = Root;
        while(x >= 0 && x < N && y >= 0 && y < M) {
            while(K != Root && !K->sons[v[x][y]])
                K = K->fail;
            if(K->sons[v[x][y]])
                K = K->sons[v[x][y]];
            if(!K->where.empty())
                for(It it = K->where.begin() ; it != K->where.end() ; ++ it)
                    ans[*it] = make_pair(dir, make_pair(x, y));
            x = x + dx[dir];
            y = y + dy[dir];
        }
    }
    inline vector <pair< int, pair<int, int> > > buildMatches(const vector <string> &v, const int &N, const int &M) {
        vector <string> x;
        for(int i = 0 ; i < N ; ++ i) {
            AhoCorasick(v, i, 0, 1, N, M);
            AhoCorasick(v, i, 0, 2, N, M);
            AhoCorasick(v, i, 0, 3, N, M);
            //AhoCorasick(v, i, M-1, 4, N, M);
            //AhoCorasick(v, i, M-1, 5, N, M);
            //AhoCorasick(v, i, M-1, 6, N, M);
        }
        for(int j = 0 ; j < M ; ++ j) {
            AhoCorasick(v, 0, j, 3, N, M);
            //AhoCorasick(v, 0, j, 4, N, M);
            //AhoCorasick(v, 0, j, 5, N, M);
            AhoCorasick(v, N-1, j, 0, N, M);
            AhoCorasick(v, N-1, j, 1, N, M);
            //AhoCorasick(v, N-1, j, 7, N, M);
        }
        return ans;
    }
private:
    Node *Root;
    vector <pair<int, pair<int, int> > > ans;
};

int T, N, M, W;
vector <string> table, words;
string line;

int main() {
    #ifndef ONLINE_JUDGE
        freopen(infile, "r", stdin);
        freopen(outfile, "w", stdout);
    #endif
    cin >> T;
    for(int test = 1 ; test <= T ; ++ test) {
        FiniteAutomaton Trie;
        cin >> N >> M >> W;
        cin.get();
        for(int i = 0 ; i < N ; ++ i) {
            getline(cin, line);
            table.push_back(line);
        }
        for(int i = 0 ; i < W ; ++ i) {
            getline(cin, line);
            Trie.addString(Trie.getRoot(), line, 0, words.size());
            words.push_back(line);
        }
        for(int i = 0 ; i < W ; ++ i) {
            line = words[i];
            reverse(line.begin(), line.end());
            Trie.addString(Trie.getRoot(), line, 0, words.size());
            words.push_back(line);
        }
        Trie.BuildFails();
        vector <pair<int, pair<int, int> > > ans = Trie.buildMatches(table, N, M);
        for(int i = 0 ; i < W ; ++ i) {
            int dir = ans[i].first;
            int x = ans[i].second.first;
            int y = ans[i].second.second;
            int sz = words[i].size();
            if(x == -1) {
                dir = ans[i+W].first + 4;
                x = ans[i + W].second.first;
                y = ans[i + W].second.second;
                sz = 1;
            }
            cout << x - (sz - 1) * dx[dir] << ' ' << y - (sz - 1) * dy[dir] << ' ' << (char)(dir + 'A') << '\n';
        }
        cout << '\n';
        vector<string>().swap(table);
        vector<string>().swap(words);
    }
    fin.close();
    fout.close();
    return 0;
}
