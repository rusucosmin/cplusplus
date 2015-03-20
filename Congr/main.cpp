#include <fstream>
#include <vector>
#include <bitset>
#include <time.h>
#include <stdlib.h>

using namespace std;

const char infile[] = "congr.in";
const char outfile[] = "congr.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 300005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, v[2*MAXN], ind[2*MAXN];
long long sum;

int main() {
    srand(time(NULL));
    fin >> N;
    int M = (N << 1);
    for(int i = 1 ; i < M ; ++ i) {
        fin >> v[i];
        if( i <= N )
            sum += v[i];
        ind[i] = i;
    }
    int ind1, ind2;
    while(sum % N) {
        ind1 = 1 + rand() % N;
        ind2 = N + 1 + (rand() % (N - 1));
        sum = sum - v[ind1] + v[ind2];
        swap(v[ind1], v[ind2]);
        swap(ind[ind1], ind[ind2]);
    }
    for(int i = 1 ; i <= N ; ++ i)
        fout << ind[i] << ' ';
    fout << "\n";
    fin.close();
    fout.close();
    return 0;
}
