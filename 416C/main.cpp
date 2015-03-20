#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector <pair<int, pair<int, int> > > v;
vector <pair<int, int> > t, vans;

struct classcomp {
    inline bool operator () (const pair<int, pair<int, int> > &a, const pair<int, pair<int, int> > &b) const {
        return a.second.second > b.second.second;
    }
};

struct classcomp2 {
    inline bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.second < b.second;
    }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("416c.in", "r", stdin);
    freopen("416c.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        int x, y;
        cin >> x >> y;
        v.push_back(make_pair(i, make_pair(x, y)));
    }
    cin >> k;
    for(int i = 1 ; i <= k ; ++ i) {
        int x;
        cin >> x;
        t.push_back(make_pair(i, x));
    }
    sort(v.begin(), v.end(), classcomp());
    sort(t.begin(), t.end(), classcomp2());
    int total = 0;
    for(int i = 0 ; i < n ; ++ i) {
        int st = 0, dr = t.size() - 1, ans = -1;
        while(st <= dr) {
            int mid = ((st + dr) >> 1);
            if(t[mid].second >= v[i].second.first) {
                dr = mid - 1;
                ans = mid;
            }
            else
                st = mid + 1;
        }
        if(ans == -1)
            continue;
        vans.push_back(make_pair(v[i].first, t[ans].first));
        total += v[i].second.second;
        t.erase(t.begin() + ans);
    }
    cout << vans.size() << ' ' << total << '\n';
    for(int i = 0 ; i < vans.size() ; ++ i)
        cout << vans[i].first << ' ' << vans[i].second << '\n';
}
