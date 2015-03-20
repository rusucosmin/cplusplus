/*
#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

const char infile[] = "string.in";
const char outfile[] = "string.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 500005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;

struct Trie {
    Trie *son[2];
    Trie() {
        memset(son, 0, sizeof(son));
    }
};

Trie *Root = new Trie();
char s[MAXN];
int lg;

void Insert(Trie * Node, char *s, int pos) {
    if(!*s || pos > lg)
        return;
    if(!Node -> son[*s - 'a'])
        Node -> son[*s - 'a'] = new Trie();
    Insert(Node -> son[*s - 'a'], s + 1, pos + 1);
}

string Query(Trie * Node) {
    if(!Node -> son[0])
        return "a";
    if(!Node -> son[1])
        return "b";
    string fst = "a" + Query(Node -> son[0]);
    string fdr = "b" + Query(Node -> son[1]);
    if(fst.size() < fdr.size())
        return fst;
    return fdr;
}

int main() {
    fin >> N;
    lg = log2(N) + 1;
    fin.get();
    fin.getline(s, MAXN);
    for(int i = 0 ; i < N ; ++ i)
        Insert(Root, s + i, 1);
    string Ans = Query(Root);
    fout << Ans.size() << '\n' << Ans;
    fin.close();
    fout.close();
    return 0;
}
*/

#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;

const char infile[] = "string.in";
const char outfile[] = "string.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 500015;
const int oo = 0x3f3f3f3f;
const int MAXX = (1 << 25);

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
char s[MAXN];
int lg;
int Ans , lengthAns = oo;
bitset < MAXX > Used;

inline bool Check(const int L) {
    Used.reset();
    int nr = 0;
    for(int i = 0 ; i < L ; ++ i)
        nr = nr * 2 + (s[i] - 'a');
    int power = (1 << L);
    Used[nr + power] = true;
    for(int i = L ; i < N ; ++ i) {
        nr = nr * 2 + (s[i] - 'a');
        nr = nr - (power * (s[i - L] - 'a'));
        Used[nr + power] = true;
    }
    for(int i = 0 ; i < (1 << L) ; ++ i)
        if(!Used[i + power]) {
            if(lengthAns > L) {
                lengthAns = L;
                Ans = i;
            }
            return true;
        }
    return false;
}

int main() {
    fin >> N;
    lg = log2(N) + 1;
    fin.get();
    fin.getline(s, MAXN);
    int li = 1, ls = lg;
    while(li <= ls) {
        int mid = ((li + ls) / 2);
        if(Check(mid))
            ls = mid - 1;
        else li = mid + 1;
    }
    assert(lengthAns != oo);
    fout << lengthAns << '\n';
    for(int i = lengthAns - 1 ; i >= 0 ; -- i)
        if(Ans & (1 << i))
            fout << 'b';
        else fout << 'a';
    //    fout << (char)('a' + ((bool) Ans & (1 << i)));
    fout << '\n';
    fin.close();
    fout.close();
    return 0;
}
