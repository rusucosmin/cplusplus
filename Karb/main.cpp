#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

const int MAXN = 100005;

typedef vector <pair<int, int> > :: iterator It;
vector < pair<int, int> > G[MAXN];
vector <pair<int, int> > Arb;

int N, M, comp, where[MAXN], Father[MAXN], FatherConex[MAXN], K;

inline void DFs(const int &Node, const int &actComp) {
    where[Node] = actComp;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!it->second && !where[it->first])
            DFs(it->first, actComp);
}

inline void UniteConex(const int &TX, const int &TY) {
    FatherConex[TX] = TY;
}

int FindConex(const int &Node) {
    if(FatherConex[Node] != Node)
        FatherConex[Node] = FindConex(FatherConex[Node]);
    return FatherConex[Node];
}

inline void Unite(const int &TX, const int &TY) {
    Father[TX] = TY;
}

int Find(const int &Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

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
Scanner fin("karb.in");

int main() {
    ofstream fout("karb.out");
    fin >> N >> M >> K;
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        fin >> x >> y >> z;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    for(int i = 1 ; i <= N ; ++ i)
        if(!where[i]) {
            DFs(i, ++ comp);
            FatherConex[comp] = comp;
        }
    int sum = 0;
    for(int i = 1 ; i <= N ; ++ i)
        for(It it = G[i].begin(), fin = G[i].end() ; it != fin ; ++ it)
            if(where[i] != where[it->first]) {
                int Tx = FindConex(where[i]);
                int Ty = FindConex(where[it->first]);
                if(Tx == Ty)
                    continue;
                Arb.push_back(make_pair(i, it->first));
                UniteConex(Tx, Ty);
                Tx = Find(i);
                Ty = Find(it->first);
                Unite(Tx, Ty);
            }
    sum += (comp - 1);
    for(int i = 1 ; i <= N && sum != K ; ++ i)
        for(It it = G[i].begin(), fin = G[i].end(); it != fin && sum != K ; ++ it) {
            int Tx = Find(i);
            int Ty = Find(it->first);
            if(it->second && Tx != Ty) {
                ++ sum;
                Arb.push_back(make_pair(i, it->first));
                Unite(Tx, Ty);
            }
        }
    for(int i = 1 ; i <= N ; ++ i)
        for(It it = G[i].begin(), fin = G[i].end(); it != fin ; ++ it)
            if(!it->second && where[i] == where[it->first]) {
                int Tx = Find(i);
                int Ty = Find(it->first);
                if(Tx == Ty)
                    continue;
                Arb.push_back(make_pair(i, it->first));
                Unite(Tx, Ty);
            }
    for(int i = 0 ; i < Arb.size() ; ++ i)
        fout << Arb[i].first << ' ' << Arb[i].second << '\n';
    return 0;
}
