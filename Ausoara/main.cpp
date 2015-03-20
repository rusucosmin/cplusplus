#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const char infile[] = "ausoara.in";
const char outfile[] = "ausoara.out";

ifstream fin(infile);
ofstream fout(outfile);

const int oo = 0x3f3f3f3f;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int main() {
    vector <int> Intersection;
    int N;
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        int K;
        fin >> K;
        vector <int> V;
        for(int j = 1 ; j <= K ; ++ j) {
            int x;
            fin >> x;
            V.push_back(x);
        }
        if(i == 1) {
            Intersection = V;
            continue;
        }
        vector <int> :: iterator it = set_intersection(V.begin(), V.end(), Intersection.begin(), Intersection.end(), Intersection.begin());
        Intersection.resize(it-Intersection.begin());
    }
    fout << Intersection.size() << ' ';
    for(vector <int> :: iterator it = Intersection.begin(), fin = Intersection.end(); it != fin ; ++ it)
        fout << *it << ' ';
    fin.close();
    fout.close();
    return 0;
}
