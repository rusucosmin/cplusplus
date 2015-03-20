#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const char infile[] = "swap.in";
const char outfile[] = "swap.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 50005;
const int oo = 0x3f3f3f3f;
const int SIGMA = 26;

char a[MAXN], b[MAXN];
int N, p[MAXN], ind[MAXN], pos[SIGMA];
vector <int> fr[SIGMA];
int aib[MAXN];

struct classComp {
    inline bool operator () (const int &a, const int &b) const {
        if(p[a] == p[b])
            return a > b;
        return p[a] > p[b];
    }
};

inline int lsb(const int &conf) {
    return conf & (-conf);
}

inline void Update(const int &Node) {
    for(int _newNode = Node ; _newNode <= N ; _newNode += lsb(_newNode))
        ++ aib[_newNode];
}

inline int Query(const int &Node) {
    int sum = 0;
    for(int _newNode = Node ; _newNode > 0 ; _newNode -= lsb(_newNode))
        sum += aib[_newNode];
    return sum;
}

int main() {
    //fin.getline(a + 1, MAXN);
    //fin.getline(b + 1, MAXN);
    fin >> (a + 1) >> (b + 1);
    for(N = 1 ; b[N] ; ++ N)
        fr[b[N] - 'a'].push_back(N);
    -- N;
    for(int i = 1 ; i <= N ; ++ i) {
        ind[i] = i;
        if(pos[a[i] - 'a'] >= fr[a[i]-'a'].size()) {
            fout << "-1\n";
            return 0;
        }
        p[i] = fr[a[i] - 'a'][pos[a[i] - 'a']];
        ++ pos[a[i] - 'a'];
    }
    sort(ind + 1, ind + N + 1, classComp());
    int Ans = 0;
    for(int i = 1 ; i <= N ; ++ i) {
        Ans += Query(ind[i]);
        Update(ind[i]);
    }
    fout << Ans << '\n';
    fin.close();
    fout.close();
    return 0;
}
