#include <fstream>
#include <map>

using namespace std;

const char infile[] = "divmul.in";
const char outfile[] = "divmul.out";

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
ofstream fout(outfile);

long long p[10000005];

inline void Desc(int x) {
    for(int i = 2 ; i * i <= x ; ++ i) {
        p[i] = 0;
        if(x % i)
            continue;
        while(x % i == 0) {
            ++ p[i];
            x /= i;
        }
    }
    if(x > 1)
        ++ p[x];
}

inline void Desc2(int x) {
    long long D = 0;
    for(int i = 2 ; i * i <= x ; ++ i) {
        if(x % i)
            continue;
        int aux = 0;
        while(x % i == 0) {
            ++ aux;
            x /= i;
        }
        if(p[i] < aux)
            ++ D;
        p[i] = 0;
    }
    if(x > 1) {
        if(p[x] < 1)
            ++ D;
    }
    fout << (1LL << D) << '\n';
}

int main() {
    int T;
    for(fin >> T ; T-- ; ) {
        int x, y;
        fin >> x >> y;
        Desc(x);
        Desc2(y);
    }
    return 0;
}
