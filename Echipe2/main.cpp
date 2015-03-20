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

string file = "echipe2";

ifstream cin( (file + ".in").c_str() );
ofstream cout( (file + ".out").c_str() );

const int MAXN = 100005;
const int oo = (1<<31)-1;

long long N, a[3][MAXN];

int main() {
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> a[0][i] >> a[1][i];
        if(a[0][i] > a[1][i])
            swap(a[0][i], a[1][i]);
    }
    long long maxiA = *max_element(a[0] + 1, a[0] + N + 1);
    long long miniA = *min_element(a[0] + 1, a[0] + N + 1);
    long long maxiB = *max_element(a[1] + 1, a[1] + N + 1);
    long long miniB = *min_element(a[1] + 1, a[1] + N + 1);
    cout << max(maxiA - miniA, maxiB - miniB);
    cin.close();
    cout.close();
    return 0;
}
