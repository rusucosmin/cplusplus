#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <string.h>

using namespace std;

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int A, B, M, Father[MAXN], last[MAXN];

inline int GCD(int A, int B) {
    int r;
    while(A % B != 0) {
        r = A % B;
        A = B;
        B = r;
    }
    return B;
}

int Ans;

#define fin cin
#define fout cout

void Write(const int &Node, const int &cnt) {
    if(Node != 1)
        Write(Father[Node], cnt + 1);
    Ans = max(Ans, cnt);
}

int main() {
    while(fin >> M) {
        Ans = 0;
        queue <int> Q;
        memset(last, 0, sizeof(last));
        memset(Father, 0, sizeof(Father));
        Q.push(1 % M);
        last[1 % M] = 2;
        Father[1 % M] = 1;
        while(!Q.empty() && last[0] == 0) {
            int actNumber = Q.front();
            Q.pop();
            for(int i = 1 ; i < 2 ; ++ i) {  /// luam cifra unu si doi
                int newNumber = (actNumber * 10 + i) % M;
                if(!last[newNumber]) {
                    Father[newNumber] = actNumber;
                    last[newNumber] = i + 1;
                    Q.push(newNumber);
                }
            }
        }
        if(last[0])
            Write(0, 1);
        fout << Ans << '\n';
    }
    return 0;
}
