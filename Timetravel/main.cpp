#include <fstream>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <string.h>

using namespace std;

const char infile[] = "timetravel.in";
const char outfile[] = "timetravel.out";

ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 1500000000;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, M, arb[MAXN << 2];
multiset <int> out[MAXN];
map <int, int> Index;
int val[MAXN];
set <int> S;

struct query {
    int op, time, val;
    query(int _op, int _time, int _val) {
        op = _op;
        time = _time;
        val = _val;
    }
};

vector <query> v;

//<parsing>
FILE* fin=fopen("timetravel.in","r");
const unsigned maxb=100;
char buf[maxb];
unsigned ptr=maxb;

inline int getInt() {
    int nr=0;
    char semn='+';
    while(buf[ptr]<'0'||'9'<buf[ptr]) {
        semn = buf[ptr];
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    while('0'<=buf[ptr]&&buf[ptr]<='9') {
        nr=nr*10+buf[ptr]-'0';
        if(++ptr>=maxb)
            fread(buf,maxb,1,fin),ptr=0;
    }
    if(semn == '-')
        nr = -nr;
    return nr;
}

void Update(const int &Node, const int &st, const int &dr, const int &pos, const int &value) {
    if(st == dr) {
        arb[Node] = value;
        return;
    }
    int mid = (st + dr) / 2;
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node + 1, mid + 1, dr, pos, value);
    arb[Node] = max(arb[2*Node], arb[2*Node + 1]);
}


int Query(const int &Node, const int &st, const int &dr, const int &a, const int &time) {
    if(dr < a || arb[Node] <= time)
        return -1;
    if(st == dr)
        return st;
    int mid = (st + dr) / 2;
    int ret = Query(2*Node, st, mid, a, time);
    if(ret == -1)
        ret = Query(2*Node + 1, mid + 1, dr, a, time);
    return ret;
}

void Build(int Node, int st, int dr) {
    if(st == dr) {
        arb[Node] = -oo;
        return;
    }
    int mid = (st + dr) / 2;
    Build(2*Node, st, mid);
    Build(2*Node + 1, mid + 1, dr);
    arb[Node] = -oo;
}

int main() {
    M = getInt();
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        x = getInt();
        if(x == 1) {
            y = getInt();
            S.insert(y);
            v.push_back(query(x, -oo, y));
            continue;
        }
        if(x == 2) {
            y = getInt();
            z = getInt();
            v.push_back(query(x, y, z));
            continue;
        }
        if(x == 3) {
            y = getInt();
            v.push_back(query(x, -oo, y));
            continue;
        }
        if(x == 4) {
            y = getInt();
            z = getInt();
            v.push_back(query(x, y, z));
            continue;
        }
        if(x == 5) {
            y = getInt();
            z = getInt();
            v.push_back(query(x, y, z));
            continue;
        }
    }
    for(set <int> :: iterator it = S.begin(), fin = S.end() ; it != fin ; ++ it) {
        Index[*it] = ++ N;
        val[N] = *it;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        out[i].insert(oo);
        out[i].insert(-oo);
    }
    Build(1, 1, N);
    map<int, int> :: iterator it;
    int x, y, z, ind = 0, k = 0, t = 0;
    for(int i = 0 ; i < M ; ++ i) {
        int x = v[i].op;
        int y = v[i].time;
        int z = v[i].val;
        if(x < 5) {
            it = Index.find(z);
            if(it == Index.end())
                continue;
            ind = it->second;
        }
        if(x == 1) {
            t = -oo;
            k = *out[ind].begin();
            out[ind].erase(t);
            if(k != *out[ind].begin())
                Update(1, 1, N, ind, *out[ind].begin());
        }
        if(x == 2) {
            k = *out[ind].begin();
            out[ind].insert(y);
            if(k != *out[ind].begin())
                Update(1, 1, N, ind, *out[ind].begin());
        }
        if(x == 3) {
            t = -oo;
            k = *out[ind].begin();
            out[ind].insert(t);
            if(k != *out[ind].begin())
                Update(1, 1, N, ind, *out[ind].begin());
        }
        if(x == 4) {
            k = *out[ind].begin();
            out[ind].erase(out[ind].find(y));
            if(k != *out[ind].begin())
                Update(1, 1, N, ind, *out[ind].begin());
        }

        if(x == 5) {
            map <int, int> :: iterator ub = Index.lower_bound(z);
            if(ub == Index.end())
                fout << "Time paradox\n";
            else {
                int position = ub->second;
                int Ans = Query(1, 1, N, position, y);
                if(Ans == -1)
                    fout << "Time paradox\n";
                else fout << val[Ans] << '\n';
            }
        }
    }
    return 0;
}
