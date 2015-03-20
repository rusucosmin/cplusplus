/*
    https://www.youtube.com/watch?v=fp3Bns-bCv4#t=87
*/
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const char infile[] = "grozavesti.in";
const char outfile[] = "grozavesti.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 305;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, a[MAXN][MAXN], p[MAXN];
vector <pair<int, int> > v;

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {  for(int j = 1 ; j <= N ; ++ j)   cin >> a[i][j];
        p[i] = a[i][i];
    }
    for(int i = N ; i >= 2 ; -- i) {
        int best = p[1], poz = 1;
        for(int j = 2 ; j <= i ; ++ j)
            if(best < p[j]) {
                best = p[j];
                poz = j;
            }
        if(i != poz) {
            v.push_back(make_pair(i, poz));
            swap(p[i], p[poz]);
        }
    }
    cout << 2 * v.size() << '\n';
    for(int i = 0 ; i < v.size() ; ++ i)
        cout << "L " << v[i].first << ' ' << v[i].second << "\nC " << v[i].first << ' ' << v[i].second << '\n';
    cin.close();
    cout.close();
    return 0;
}
