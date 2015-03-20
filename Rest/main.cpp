#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "rest.in";
const char outfile[] = "rest.out";

//ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 250005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, powB[MAXN / 2], P, B;
int arb[MAXN << 2];

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

void Update(int Node, int st, int dr, int pos, int value) {
    if(st == dr) {
        arb[Node] = value;
        return;
    }
    int mid = (st + dr) / 2;
    if(pos <= mid)
        Update(2*Node, st, mid, pos, value);
    else Update(2*Node+1, mid + 1, dr, pos, value);
    arb[Node] = ((arb[2*Node] * powB[dr - mid]) + arb[2*Node + 1]) % P;
}

int Query(int Node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b) {
        return arb[Node];
    }
    int mid = (st + dr) / 2;
    int ret = 0;
    if(a <= mid)
        ret = Query(2*Node, st, mid, a, b);
    if(mid < b)
        ret = (ret * powB[min(b, dr) - mid] + Query(2*Node + 1, mid + 1, dr, a, b)) % P;
    return ret;
}

int main() {
    Scanner fin(infile);
    fin >> N >> B >> P;
    powB[1] = B % P;
    for(int i = 2 ; i <= N / 2 + 1 ; ++ i)
        powB[i] = (powB[i - 1] * B) % P;
    for(int i = 1 ; i <= N  ; ++ i) {
        int x;
        fin >> x;
        Update(1, 1, N, i, x % P);
    }
    fin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        fin >> op >> x >> y;
        if(op == 1)
            Update(1, 1, N, x, y % P);
        else {
            fout << Query(1, 1, N, x, y) << '\n';
        }
    }
    fout.close();
    return 0;
}
