#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, h;
vector <pair<int, int> >  x;

int main() {
    ifstream fin("patrate1.in");
    ofstream fout("patrate1.out");
    fin >> n >> h;
    for(int i = 0 ; i < n ; ++ i) {
        int c, p;
        fin >> c >> p;
        x.push_back(make_pair(c, -1));
        x.push_back(make_pair(c + p, 1));
    }
    sort(x.begin(), x.end());
    int sum = 0, ans = 0, start = 0, beg = -1;
    for(int i = 0 ; i < x.size() ; ++ i) {
        if(sum == h - 1 && x[i].second == -1)
            beg = x[i].first;
        else
            if(sum == h && x[i].second == 1) {
                if(ans < x[i].first - beg) {
                    ans = x[i].first - beg;
                    start = beg;
                }
            }
        sum -= x[i].second;
    }
    fout << start <<  ' ' << ans << '\n';
}
