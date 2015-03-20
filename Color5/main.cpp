#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "color5.in";
const char outfile[] = "color5.out";

ifstream fin(infile);
ofstream fout(outfile);

inline void Solve(const int &N) {
    if(N == 3) {
        fout << "1\n";
        for(int i = 0 ; i < N ; ++ i)
            fout << i << ' ' << N << ' ' << 1 << '\n';
        for(int i = 0 ; i < N ; ++ i)
            fout << i << ' ' << (i + 1) % N << ' ' << 1 << '\n';
        return;
    }
    if(N < 7) {
        fout << "2\n";
        for(int i = 0 ; i < N ; ++ i)
            fout << i << ' ' << N << ' ' <<  (i % 2) + 1 << '\n';
        for(int i = 0 ; i < N ; ++ i)
            fout << i << ' ' << (i + 1) % N << ' ' << (i % 2) + 1 << '\n';
        return;
    }
    fout << "3\n";
    for(int i = 0 ; i < N ; ++ i)
        fout << i << ' ' << N << ' ' << (i % 2) + 1 << '\n';
    for(int i = 0 ; i < N ; ++ i)
        fout << i << ' ' << (i + 1) % N << ' ' << "3\n";
}

int main() {
    int N;
    fin >> N;
    Solve(N);
    fin.close();
    fout.close();
    return 0;
}
