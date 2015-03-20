#include <fstream>
#include <vector>
#include <bitset>
#include <deque>

using namespace std;

const char infile[] = "buline.in";
const char outfile[] = "buline.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int A[MAXN << 1], N, best, _sta, _end;
deque <int> dq;

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        bool x;
        fin >> A[i] >> x;
        if(!x)
            A[i] *= -1;
    }
    for(int i = N + 1 ; i < (N << 1) ; ++ i)
        A[i] = A[i - N];
    for(int i = 1 ; i < (N << 1) ; ++ i)
        A[i] += A[i-1];
    for(int i = 1 ; i < (N << 1) ; ++ i) {
        while(!dq.empty() && i - dq.front() >= N)
            dq.pop_front();
        while(!dq.empty() && A[dq.back()] > A[i])
            dq.pop_back();
        dq.push_back(i);
        if(best < A[i] - A[dq.front()]) {
            best = A[i] - A[dq.front()];
            _sta = dq.front() + 1;
            _end = i - dq.front();
        }
    }
    fout << best << ' ' << _sta << ' ' << _end << '\n';
    fin.close();
    fout.close();
    return 0;
}
