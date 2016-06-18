#include <bits/stdc++.h>

using namespace std;

inline void print(int x) {
    cout << (char)(x + 'A') << ' ';
}

inline void print(int x, int y) {
    cout << (char)(x + 'A') << (char)(y + 'A') << ' ';
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    int t;
    cin >> t;
    int test = 0;
while(t --) {
    int n;
    cin >> n;
    cout << "Case #" << ++ test << ": ";
    priority_queue <pair<int, int> > q;
    vector <int> done;
    for(int i = 0 ; i < n ; ++ i) {
        int x;
        cin >> x;
        if(x == 1)
            done.push_back(i);
        else
        q.push(make_pair(x, i));
    }
    while(q.size() >= 2) {
        pair<int, int> one = q.top(); q.pop();
        pair<int, int> two = q.top(); q.pop();
        if(one.first > two.first) {
            print(one.second);
            one.first --;
        }
        else {
            one.first --;
            two.first --;
            print(one.second, two.second);
        }
        if(one.first > 1)
            q.push(one);
        else
            done.push_back(one.second);
        if(two.first > 1)
            q.push(two);
        else
            done.push_back(two.second);
    }
    while(q.size()) {
        pair<int, int> one = q.top(); q.pop();
        print(one.second);
        one.first --;
        if(one.first > 1)
            q.push(one);
        else
            done.push_back(one.second);
    }
    if(done.size() % 2) {
        print(done.back());
        done.pop_back();
    }
    while(done.size()) {
        print(done[done.size() - 1], done[done.size() - 2]);
        done.pop_back();
        done.pop_back();
    }
    cout << '\n';
}
    return 0;
}
