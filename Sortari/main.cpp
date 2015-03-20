#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "sortari.in";
const char outfile[] = "sortari.out";

ifstream fin(infile);
ofstream fout(outfile);

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
vector <pair<int, int> > swaps;

inline int Validate(void) {
    int maxConf = (1 << N);
    for(int conf = 0 ; conf < maxConf ; ++ conf) {
        int clone = conf;
        for(vector <pair<int, int> > :: iterator it = swaps.begin(), fin = swaps.end(); it != fin ; ++ it) {
            if((clone & (1 << (it->first))) > (clone & (1 << (it->second)))) {
                clone ^= (1 << it->first);  /// 1 ^ 1 = 0
                clone ^= (1 << it->second); /// 0 ^ 0 = 1
            }
        }
        for(int i = 1 ; i < N ; ++ i)
            if((clone & (1 << (i))) < (clone & (1 << (i - 1))))
                return 0;
        }
    return 1;
}

int main() {
    int T;
    fin >> T;
    while(T -- ) {
        int M;
        fin >> N >> M;
        while(M -- ) {
            int x, y;
            fin >> x >> y; -- x; -- y;
            swaps.push_back(make_pair(x, y));
        }
        fout << Validate() << '\n';
        vector <pair<int, int> > () .swap(swaps); /// if you know what i mean
    }
    fin.close();
    fout.close();
    return 0;
}
