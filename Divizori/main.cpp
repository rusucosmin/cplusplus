#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const char infile[] = "divizori.in";
const char outfile[] = "divizori.out";

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

int N;
vector <int> d, p;
stack <int> st;
set <int> Used;

void print(stack <int> st) {
    int Node = st.top();
    st.pop();
    if(!st.empty())
        print(st);
    fout << Node << ' ';
}

void Back(int K) {
    if(K == d.size()) {
        fout << d.size() << '\n';
        print(st);
        exit(0);
    }
    for(vector <int> :: iterator it = p.begin(), fin = p.end(); it != fin ; ++ it) {
        if(st.top() % *it == 0 && Used.find(st.top() / *it) == Used.end()) {
            Used.insert(st.top() / *it);
            st.push(st.top() / *it);
            Back(K + 1);
            st.pop();
            Used.erase(st.top() / *it);
        }
        if(Used.find(st.top() * *it) == Used.end() && (d.back() % (st.top() * *it)) == 0) {
            Used.insert(st.top() * *it);
            st.push(st.top() * *it);
            Back(K + 1);
            st.pop();
            Used.erase(st.top() * *it);
        }
    }
}

int main() {
    fin >> N;
    int i;
    for(i = 1 ; i * i < N ; ++ i)
        if(N % i == 0) {
            d.push_back(i);
            d.push_back(N / i);
        }
    if(i * i == N)
        d.push_back(N);
    sort(d.begin(), d.end());
    for(i = 2 ; i * i <= N ; ++ i) {
        if(N % i)
            continue;
        p.push_back(i);
        while(N % i == 0)
            N /= i;
    }
    if(N > 1)
        p.push_back(N);
    Used.insert(1);
    st.push(1);
    Back(1);
    fin.close();
    fout.close();
    return 0;
}
