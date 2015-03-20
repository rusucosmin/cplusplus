#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 50005;

long long t, n, p;
vector <pair<long long, long long> > v;
long long l;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE

    cin >> t;
    for(long long test = 1 ; test <= t ; ++ test) {
        cin >> n;
        v.clear();
        for(long long i = 0 ; i < n ; ++ i) {
            long long x;
            long long y;
            cin >> x >> y;
            v.push_back(make_pair(x, y));
        }
        cin >> l >> p;
        v.push_back(make_pair(0, 0));
        v.push_back(make_pair(l, p));
        sort(v.begin(), v.end(), greater <pair<long long, long long> > ());
        long long ans = -1;
        priority_queue <long long> q;
        bool impossible = false;
        l = v[0].first;
        p = 0;
        for(int i = 0 ; i < v.size() && !impossible ; ++ i) {
            p = p - (l - v[i].first);
            l = v[i].first;
            while(!q.empty() && p < 0) {
                p += q.top();
                ///cerr << "purchasing " << q.top() << '\n';
                q.pop();
                ++ ans;
            }
            if(p < 0) {
                impossible = true;
                break;
            }
            q.push(v[i].second);
        }
        if(impossible)
            cout << "-1\n";
        else
            cout << ans << '\n';
    }
}
