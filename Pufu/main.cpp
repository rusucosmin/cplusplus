#include <fstream>
#include <vector>
#include <bitset>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

const char infile[] = "pufu.in";
const char outfile[] = "pufu.out";

ifstream cin(infile);
ofstream cout(outfile);

const int MAXN = 4005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int fr[3];

int main() {
    int T;
    cin >> T;
    int N;
    while( T -- ) {
        cin >> N;
        string b;
        for(int i = 1 ; i <= N ; ++ i) {
            cin >> b;
            if(b == "ciocolata")
                ++ fr[0];
            else if(b == "cascaval")
                ++ fr[1];
            else ++ fr[2];
        }
        for(int i = 0 ; i < 3; ++ i)
            cout << fr[i] << ' ' , fr[i] = 0;
        cout << '\n';
    }
    cin.close();
    cout.close();
    return 0;
}
