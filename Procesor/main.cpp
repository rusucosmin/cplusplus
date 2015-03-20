#include <fstream>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

ifstream fin("procesor.in");
ofstream fout("procesor.out");

const int MAXN = 100005;

int N;
pair <int, int> Task[MAXN];

struct heapComp {
    inline bool operator () (const int &a, const int &b) const {
        return Task[a].second < Task[b].second;
    }
};

priority_queue <int, vector <int>, heapComp> Heap;

struct classComp {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.first > b.first;
    }
};

int main() {
    fin >> N;
    for(int i = 1 ; i <= N ; ++i)
        fin >> Task[i].first >> Task[i].second;
    sort(Task + 1, Task + N + 1, classComp());
    for(int i = Task[1].first, j = 1 ; i >= 1 ; -- i) {
        while(j <= N && Task[j].first >= i)
            Heap.push(j ++);
        if(!Heap.empty())
            Heap.pop();
    }
    long long ans = 0;
    while(!Heap.empty()) {
        ans += Task[Heap.top()].second;
        Heap.pop();
    }
    fout << ans << '\n';
    return 0;
}
