#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const char infile[] = "flux2.in";
const char outfile[] = "flux2.out";

ofstream fout(outfile);

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

typedef vector< int > Graph[MAXN];
typedef vector< int > :: iterator It;

int N, M, S, D, dist[MAXN], inQs[MAXN];
Graph G;
vector<pair<int, int> > E[MAXN];
bitset <MAXN> inQ;
queue <int> Q;

class Scanner {
  public:
    Scanner(string file, int buffer_size = 32768):
            buffer_size_(buffer_size) {
        file_ = fopen(file.c_str(), "r");
        buffer_ = new char[buffer_size];
        pointer_ = buffer_ + buffer_size_;
    }

    Scanner& operator>>(int &object) {
        object = 0;
        while (next() < '0' or next() > '9')
            advance();
        while (next() >= '0' and next() <= '9') {
            object = object * 10 + next() - '0';
            advance();
        }
        return *this;
    }

  private:
    char next() {
        if (pointer_ == buffer_ + buffer_size_) {
            pointer_ = buffer_;
            fread(buffer_, 1, buffer_size_, file_);
        }
        return *pointer_;
    }

    void advance() {
        ++pointer_;
    }

    FILE *file_;
    int buffer_size_;
    char *buffer_, *pointer_;
};

Scanner fin(infile);

inline bool BFs(const int &startNode) {
    inQ.reset();
    while(!Q.empty())
        Q.pop();
    Q.push(startNode);
    inQ[startNode] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == D)
            return true;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!inQ[*it]) {
                Q.push(*it);
                inQ[*it] = true;
            }
    }
    return false;
}

inline bool negativeCycle() {
    inQ.reset();
    while(!Q.empty())
        Q.pop();
    //for(int startNode = 1 ; startNode <= N ; ++ startNode) {
        int startNode = 0;
        memset(dist, oo, sizeof(dist));
        memset(inQs, 0, sizeof(inQs));
        Q.push(startNode);
        dist[startNode] = 0;
        inQ[startNode] = true;
        while(!Q.empty()) {
            int Node = Q.front();
            Q.pop();
            inQ[Node] = false;
            for(vector<pair<int, int> > :: iterator it = E[Node].begin(), fin = E[Node].end(); it != fin ; ++ it)
                    if(dist[it->first] > dist[Node] + it->second) {
                        dist[it->first] = dist[Node] + it->second;
                        if(!inQ[it->first]) {
                            if(inQs[it->first] >= N)
                                return true;
                            ++ inQs[it->first];
                            inQ[it->first] = true;
                            Q.push(it->first);
                        }
                    }
        }
    //}
    return false;
}

int main() {
    int T;
    fin >> T;
    while( T -- ) {
        for(int i = 1 ; i <= N ; ++ i) {
            vector <int> ().swap(G[i]);
            vector <pair<int, int> > ().swap(E[i]);
        }
        fin >> N >> M >> S >> D;
        for(int i = 1 ; i <= M ; ++ i) {
            int a, b, c, d, e;
            fin >> a >> b >> c >> d >> e;
            if(e - d > 0)
                G[a].push_back(b);
            if(d < e) {
                E[0].push_back(make_pair(a, 0));
                E[a].push_back(make_pair(b, c));
            }
            if(d > 0) {
                E[0].push_back(make_pair(b, 0));
                E[b].push_back(make_pair(a, -c));
            }
        }
        if(BFs(S) || negativeCycle()) {
            fout << "0\n";
            continue;
        }
        fout << "1\n";
    }
    return 0;
}
