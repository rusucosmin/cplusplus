#include <fstream>
//#include <vector>
#include <queue>
using namespace std;

string file = "proc2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

priority_queue < pair<int, int> , vector<pair<int, int> > , greater <pair <int, int> > > Q;
priority_queue < int , vector <int>, greater <int> > qInd;

int N, M;

int main() {
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i)
        qInd.push(i);
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b;
        cin >> a >> b;
        while(!Q.empty() && Q.top().first <= a) {
            qInd.push(Q.top().second);
            Q.pop();
        }
        Q.push(make_pair(a + b, qInd.top()));
        cout << qInd.top() << '\n';
        qInd.pop();
    }
    cin.close();
    cout.close();
    return 0;
}
