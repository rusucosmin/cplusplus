#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "expectedpos.in";
const char outfile[] = "expectedpos.out";

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
        int sgn = 1;
        while (next() < '0' or next() > '9') {
            if(next() == '-')
                sgn = -1;
            advance();
        }
        while (next() >= '0' and next() <= '9') {
            object = object * 10 + next() - '0';
            advance();
        }
        object *= sgn;
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

vector <int> a;
int N, K, Q;

int GCD(const int &a, const int &b) {
    if(b == 0)
        return a;
    return GCD(b, a % b);
}

int main() {
    fin >> N >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        fin >> x;
        for(int j = 1 ; j <= x ; ++ j) {
            int y;
            fin >> y;
            a.push_back(y);
        }
    }
    sort(a.begin(), a.end());
    fin >> Q;
    for(int i = 1 ; i <= Q; ++ i) {
        int x;
        fin >> x;
        int pos = (upper_bound(a.begin(), a.end(), x) - a.begin() + 1) + K - 1;
        int cmmdc = GCD(pos, K);
        fout << (pos / cmmdc) << '/' << (K / cmmdc) << '\n';
    }
    return 0;
}
