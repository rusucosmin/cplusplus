#include <fstream>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

const char infile[] = "multiplu.in";
const char outfile[] = "multiplu.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 2000005;
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

void Write(const int &Node) {
    if(Node != 1) {
        Write(Father[Node]);
    }
    fout << last[Node] - 1;
}

int main() {
    queue <int> Q;
    fin >> A >> B;
    M = (A * B) / GCD(A, B);
    Q.push(1 % M);
    last[1 % M] = 2;
    Father[1 % M] = 1;
    while(!Q.empty() && last[0] == 0) {
        int actNumber = Q.front();
        Q.pop();
        for(int i = 0 ; i < 2 ; ++ i) {  /// luam cifra unu si doi
            int newNumber = (actNumber * 10 + i) % M;
            if(!last[newNumber]) {
                Father[newNumber] = actNumber;
                last[newNumber] = i + 1;
                Q.push(newNumber);
            }
        }
    }
    Write(0);
    fin.close();
    fout.close();
    return 0;
}
