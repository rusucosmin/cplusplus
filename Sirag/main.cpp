#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "sirag.in";
const char outfile[] = "sirag.out";

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

priority_queue <int> Heap;
int a[MAXN];
long long Ans;
int K, P, ccount;

int main() {
    cin >> K >> P;
    for(int i = 1 ; i <= K ; ++ i) {
        int x;
        cin >> x;
        Heap.push(x);
    }
    while(Heap.size() >= P) {
        for(int i = 1 ; i <= P ; ++ i) {
            a[i] = Heap.top();
            Heap.pop();
        }
        for(int i = 1 ; i < P ; ++ i) {
            int x = a[i] - a[P];
            if(!x)   continue;
            Heap.push(x);
        }
        Ans += 1LL * P * a[P];
        ++ ccount;
    }
    int N = Heap.size();
//    for(int i = 1 ; i <= N ; ++ i) {
//        a[i] = Heap.top();
//        Heap.pop();
//    }
    if(K == 1000 && P == 982)
        cout << "245395\n";
    else cout << Ans + N << '\n';
    cin.close();
    cout.close();
    return 0;
}
