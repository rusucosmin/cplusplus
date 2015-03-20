#include <fstream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

const char infile[] = "swaps2.in";
const char outfile[] = "swaps2.out";

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

int main() {
    int N;
    string S;
    cin >> N >> S;
    int li = 0, ls = N-1;
    vector <pair<int, int> > swaps;
    while(li < ls) {
        while(li < ls && S[li] == '0') ++ li;
        while(li < ls && S[ls] == '1') -- ls;
        if(li < ls) {
            swaps.push_back(make_pair(li, ls));
            ++ li;
            -- ls;
        }
    }
    cout << swaps.size() << '\n';
    for(int i = 0 ; i < swaps.size() ; ++ i)
        cout << swaps[i].first + 1 << ' ' << swaps[i].second + 1 << '\n';
    cin.close();
    cout.close();
    return 0;
}
