#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>

using namespace std;

const char infile[] = "enigma.in";
const char outfile[] = "enigma.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 300005;
const int MOD = 31333;
const int MAXS = 105;
const int ALFA = 30;
const int oo = 0x3f3f3f3f;

int N, M;
int dp[MAXN]; /// dp[i] = numarul de posibilitati de a scrie sirul s[0:i]
char S[MAXN], C[MAXN];

struct Trie {
    int freq;
    Trie *son[ALFA];
    Trie() {
        freq = 0;
        memset(son, 0, sizeof(son));
    }
};

Trie *Root = new Trie;

void Insert(Trie *Node, char *word) {
    if(Node != Root)
        ++ Node -> freq;
    if(!*word)
        return;
    if(!Node->son[*word - 'a'])
        Node->son[*word - 'a'] = new Trie;
    Insert(Node->son[*word - 'a'], word + 1);
}

void Query(Trie *Node, char *word, const int &index) {
    if(Node -> freq)
        dp[word - S] = (dp[word - S] + dp[index] * Node -> freq) % MOD;
    if(!*word || !Node -> son[*word - 'a'])
        return;
    Query(Node -> son[*word - 'a'], word + 1, index);
}

int main() {
    cin >> N >> M >> S;
    for(int i = 1 ; i <= M ; ++ i) {
        cin >> C;
        Insert(Root, C);
    }
    dp[0] = 1;
    for(int i = 0 ; i < N ; ++ i)
        if(dp[i])
            Query(Root, S + i, i);
    cout << dp[N] << '\n';
    cin.close();
    cout.close();
    return 0;
}
