#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <list>
#include <iomanip>

using namespace std;

string file = "scara3";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 1205;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct ClassComp {
    inline bool operator () (const int &a, const int &b) const {
        return a > b;
    }
};

int N, K, L, Water[MAXN], Drink[MAXN];
vector<int> P(MAXN, oo), C(MAXN, oo);
bitset<MAXN> Marked;
queue<int> Q;

inline void Shuffle() {
    C[1] = 0;
    P[1] = 1;
    for(Q.push(1) ; !Q.empty() ; Q.pop() ) {
        int i = Q.front();
        if(Water[i]) {
            for(int j = 1 ; j <= Water[i] ; ++ j) {
                int newNode = i + j;
                if(newNode > N)
                    break;
                if(P[newNode] > P[i] + 1 || (P[newNode] == P[i] + 1 && C[newNode] > C[i])){
                    P[newNode] = P[i] + 1;
                    C[newNode] = C[i];
                    Q.push(newNode);
                }
            }
        }
        if(Drink[i]) {
            for(int j = 1 ; j <= 2*Drink[i] ; ++ j) {
                int newNode = i + j;
                if(newNode > N)
                    break;
                if(P[newNode] > P[i] + 1 || (P[newNode] == P[i] + 1 && C[newNode] > C[i] + (j+1)/2)){
                    P[newNode] = P[i] + 1;
                    C[newNode] = C[i] + (j+1)/2;
                    Q.push(newNode);
                }
            }
        }
        /// Urc o scara => i , i + 1
        if( i < N ){
            int newNode = i + 1;
            if(P[newNode] > P[i] + 1 || (P[newNode] == P[i] + 1 && C[newNode] > C[i])){
                P[newNode] = P[i] + 1;
                C[newNode] = C[i];
                Q.push(newNode);
            }
        }
    }

}

int main() {
    cin >> N >> K;
    for(int i = 1 ; i <= K ; ++ i) {
        int x, y;
        cin >> x >> y;
        Water[x] = y;
    }
    cin >> L;
    for(int i = 1 ; i <= L ; ++ i) {
        int x, y;
        cin >> x >> y;
        Drink[x] = y;
    }
    Shuffle();
    //for(int i = 1 ; i <= N ; ++ i)
        cout << P[N] << ' ' << C[N] << '\n';
    cin.close();
    cout.close();
    return 0;
}
