#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>

using namespace std;

const char infile[] = "stalpi.in";
const char outfile[] = "stalpi.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const long long oo = 0x3f3f3f3f;

struct Pillar {
    int x, s, d, c;
};

Pillar P[MAXN], S[MAXN];

int N;
long long dp[MAXN];

struct classComp1 {
    inline bool operator () (const Pillar &a, const Pillar &b) const {
        return a.x < b.x;
    }
};

struct classComp2 {
    inline bool operator () (const Pillar &a, const Pillar &b) const {
        if(a.s != b.s)
            return a.s < b.s;
        return a.d < b.d;
    }
};

template <class T>
class biTree {
public:
    biTree() {
        memset(tree, oo, sizeof(tree));
    }
    void update(const int &Node, const T &value) {
        for(int _Node = Node ; _Node ; _Node -= (lsb(_Node)))
            tree[_Node] = min(tree[_Node], value);
    }
    T find(const int &Node) {
        long long ret = oo;
        for(int _Node = Node ; _Node <= N ; _Node += (lsb(_Node)))
            ret = min(ret, tree[_Node]);
        return ret;
    }
private:
    T tree[MAXN];
    const inline int lsb(const int &conf) const {
        return conf & ( - conf);
    }
};

inline int binarySearchLeft(const int &value) {
    int li = 1, ls = N, ret = 0;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(P[mid].x >= value) {
            ret = mid;
            ls = mid - 1;
        }
        else li = mid + 1;
    }
    return ret;
}

inline int binarySearchRight(const int &value) {
    int li = 0, ls = N, ret = 0;
    while(li <= ls) {
        int mid = ((li + ls) >> 1);
        if(P[mid].x <= value) {
            ret = mid;
            li = mid + 1;
        }
        else ls = mid - 1;
    }
    return ret;
}

biTree <long long> Tree;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        fin >> P[i].x >> P[i].c >> P[i].s >> P[i].d;
        S[i].s = P[i].x - P[i].s;
        S[i].d = P[i].x + P[i].d;
        S[i].c = P[i].c;
    }
    sort(P + 1, P + N + 1, classComp1());
    sort(S + 1, S + N + 1, classComp2());

    memset(dp, oo, sizeof(dp));

    long long temp = 0;

    for(int i = 1 ; i <= N ; ++ i) {
        int left = binarySearchLeft(S[i].s) - 1;
        int right = binarySearchRight(S[i].d);
        if(!left)
            temp = 0;
        else temp = Tree.find(left);
        temp += S[i].c;
        if(temp < dp[right]) {
            dp[right] = temp;
            Tree.update(right, temp);
        }
    }
    fout << dp[N] << '\n';
    fin.close();
    fout.close();
    return 0;
}
