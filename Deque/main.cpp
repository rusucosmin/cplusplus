#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

ifstream fin("deque.in");
ofstream fout("deque.out");

const int maxn = 5000005;

int n, k, a[maxn];
deque <int> dq;

int main() {
    fin >> n >> k;
    long long sum = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        fin >> a[i];
        while(!dq.empty() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);
        if(i - dq.front() >= k)
            dq.pop_front();
        if(i >= k)
            sum += a[dq.front()];
           // , cerr << a[dq.front()] << '\n';
    }
    fout << sum << '\n';
}
