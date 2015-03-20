#include <fstream>
#include <vector>
#include <bitset>
#include <memory.h>
#include <iostream>

using namespace std;

const char infile[] = "xormax.in";
const char outfile[] = "xormax.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int SIGMA = 2;
const int MAXBITI = 21;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct Trie {
    int where;
    Trie *son[2]; /// SIGMA is the alphabet, where is { 0,  1} ;
    Trie() {
        where = 0;
        memset(son, 0, sizeof(son));
    }
};

int N, dp[MAXN], maxXor = -1; /// dp[i] = the xor of the first i-th numbers
Trie * Root = new Trie();

void Insert(Trie *Node, const int where, const int pos, const int nr) {
    if(pos == -1) {
        Node -> where = where;
        return;
    }
    bool actSon = nr & ( 1 << pos );
    if(!Node -> son[actSon])
        Node -> son[actSon] = new Trie();
    Insert(Node -> son[actSon], where, pos - 1, nr);
}

int Query(Trie *Node, const int &pos, const int &nr) {
    if(pos == -1)
        return Node->where;
    bool actSon = nr & ( 1 << pos );
    if(!Node -> son[!actSon])
        return Query(Node -> son[actSon], pos - 1, nr);
    return Query(Node -> son[!actSon], pos - 1, nr);
}

int main() {
    int st, fn;
	int t;
	cin >> t;
	while(t --) {
		Root = new Trie();
		maxXor = -1;
    	cin >> N;
    	Insert(Root, 0, 31, 0);
    	for(int i = 1 ; i <= N ; ++ i) {
       	 	int x;
       		cin >> x;
        	dp[i] = dp[i - 1] ^ x;
        	int pos = Query(Root, 31, dp[i]);
        	if( ( dp[pos] ^ dp[i]) > maxXor) {
           	 	maxXor = (dp[pos] ^ dp[i]);
            	st = pos + 1;
            	fn = i;
        	}
       	 	Insert(Root, i, 31, dp[i]);
    	}
    	cout << maxXor << ' ';
	}
    return 0;
}
