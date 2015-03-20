/// poo concepts
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "fabrica.in";
const char outfile[] = "fabrica.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, A, B, timeA[MAXN], timeB[MAXN];

template <class T>
class Heap {
private:
    priority_queue < pair<int, int> , vector <pair<int, int> >, greater <pair<int, int> > > Q;
    void _Clear() {
        while(!Q.empty()) Q.pop();
    }
    void _Update(const int &N, int *time) {
        for(int i = 1 ; i <= N ; ++ i) {
            time[i] = Q.top().first;
            Q.push(make_pair(Q.top().first + Q.top().second, Q.top().second));
            Q.pop();
        }
    }
    void _Add(const int &Value) {
        Q.push(make_pair(Value, Value));
    }
    int _getTop() {
        return Q.top().first;
    }
public:
    void Clear() {
        _Clear();
    }
    void Update(const int &N, int *time){
        _Update(N, time);
    }
    int getTop() {
        return _getTop();
    }
    void Add(const int &Value){
        _Add(Value);
    }
};

int main() {
    Heap < pair<int, int> > Q;
    fin >> N >> A >> B;
    for(int i = 1 ; i <= A ; ++ i) {
        int x;
        fin >> x;
        Q.Add(x);
    }
    Q.Update(N, timeA);
    Q.Clear();
    for(int i = 1 ; i <= B ; ++ i) {
        int x;
        fin >> x;
        Q.Add(x);
    }
    Q.Update(N, timeB);
    fout << timeA[N] << ' ';
    for(int i = 1 ; i <= N ; ++ i)
        timeB[0] = max(timeB[0], timeA[i] + timeB[N - i + 1]);
    fout << timeB[0] << '\n';
    fin.close();
    fout.close();
    return 0;
}
