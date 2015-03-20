#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("secv9.in");
ofstream cout("secv9.out");

const int MAXN = 100005;

int N, S;
pair<int, int> a[MAXN];

int main() {
    cin >> N >> S;
    for(int i = 1; i <= N; ++ i) {
        int x;
        cin >> x;
        a[i].first = a[i - 1].first + x;
        a[i].second = i;
    }
    sort(a, a + N + 1);
    int j = 0;
    int minIndex = a[0].second;
    int ans = 0;
    for(int i = 0 ; i <= N ; ++ i) {
        while(a[i].first - a[j + 1].first >= S && j + 1 <= N)
            minIndex = min(minIndex, a[++ j].second);
        if(a[i].first - a[j].first >= S)
            ans = max(ans, a[i].second - minIndex);
    }
    cout << ans << '\n';
    cin.close();
    cout.close();
    return 0;
}
