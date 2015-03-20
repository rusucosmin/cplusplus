/*
	Before sending this to judge, I must say that I was blessed that I managed to get what I was doing wrong :)

*/
#include <iostream>
#include <vector>
#include <string.h>
 
using namespace std;
 
const int lim = (1 << 20);
int pos;
char buff[lim];
 
inline void getint(int &x) {
	x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}
 
const int maxn = 50005;
 
int n, m, t, bt;
int a, b, c, d, type;
 
struct trie {
    int cnt[2];
    trie *sons[2];
    trie() {
        memset(cnt, 0, sizeof(cnt));
        memset(sons, 0, sizeof(sons));
    }
	void update() {
		cnt[0] = cnt[1] = 0;
		for(int i = 0 ; i < 2 ; ++ i) {
			if(!sons[i])
				continue;
			cnt[0] += sons[i]->cnt[0];
			cnt[1] += sons[i]->cnt[1];
		}
	}
} *arb[maxn << 2];
 
inline void add(trie *&node, int ty, int bit) {
    if(bit == -1) {
        node->cnt[c] += d;
        return;
    }
	bool aux = 0;
	if(ty & (1 << bit))
		aux = 1;
    if(!node->sons[aux])
        node->sons[aux] = new trie();
    add(node->sons[aux], ty, bit - 1);
	node->update();
}

inline void update(int node, int st, int dr, int pos) {
    if(st == dr) {
        if(!arb[node])
            arb[node] = new trie();
        add(arb[node], b, bt);
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        update((node << 1), st, mid, pos);
    else
        update(((node << 1) + 1), mid + 1, dr, pos);
    if(!arb[node])
        arb[node] = new trie();
    add(arb[node], b, bt);
}
 
vector < trie * > v;
 
inline void query(int node, int st, int dr) {
    if(a <= st && dr <= b) {
        v.push_back(arb[node]);
        return ;
    }
    int mid = ((st + dr) >> 1);
    if(a <= mid)
        query(node << 1, st, mid);
    if(mid < b)
        query(((node << 1) + 1), mid + 1, dr);
}
 
inline int solve() {
    trie *aux;
    int nr = 0;
	vector <trie * > nxt[2];
    for(int bit = bt ; bit >= 0 ; -- bit) {
		int sum = 0;
        for(vector <trie*> :: iterator it = v.begin() ; it != v.end() ; ++ it) {
            aux = *it;
            if(aux && aux->sons[0])
                sum += aux->sons[0]->cnt[c];
			if(aux && aux->sons[0])
				nxt[0].push_back(aux->sons[0]);
			if(aux && aux->sons[1])
				nxt[1].push_back(aux->sons[1]);
        }
		bool son = 0;
		if(d > sum) {
			d -= sum;
			son = 1;
		}
		nr = nr * 2 + son;
		v.clear();
		v = nxt[son];
		nxt[0].clear();
		nxt[1].clear();	
    }
    return nr;
}

inline pair<int, int> get(trie *&node, int ty, int bit) {
	if(bit == -1)
		return make_pair(node->cnt[0], node->cnt[1]);
	bool son = (ty & (1 << bit));
	return get(node->sons[son], ty, bit - 1);
}
 
int main() {
    freopen("kinder.in", "r", stdin);
	freopen("kinder.out", "w", stdout);
    getint(n);
    getint(m);
    getint(t);
    while((1 << bt) <= m)
        ++ bt;
	-- bt;
    for(int op = 1; op <= t; ++ op) {
        getint(type);
        if(type == 1) {
            getint(a);
            getint(b);
            getint(c);
            getint(d);
            update(1, 1, n, a);
        }
        else if(type == 2) {
            getint(a);
            getint(b);
			int x = a;
			int y = b;
			a = a;
			b = a;
			v.clear();
			query(1, 1, n);
			pair<int, int> numaistiucenumesadaulavariabila = get(v[0], y, bt);
			c = 0;
			d = -numaistiucenumesadaulavariabila.first + numaistiucenumesadaulavariabila.second;
			b = y;
			update(1, 1, n, a);
			c = 1;
			d = -d;
			update(1, 1, n, a);
        }
        else {
            getint(a);
            getint(b);
            getint(c);
            getint(d);
            v.clear();
            query(1, 1, n);
           	printf("%d\n", solve()); 
        }
    }
}
