#include <fstream>
#include <vector>
#include <bitset>
#include <string.h>
#include <set>
#include <queue>
 
using namespace std;
 
const char infile[] = "cifre4.in";
const char outfile[] = "cifre4.out";
 
ifstream fin(infile);
ofstream fout(outfile);
 
const int MAXN = 5000005;
const int oo = 0x3f3f3f3f;
 
typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;
 
const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }
 
set <int> digits;
queue <int> Q;
int Father[MAXN], digit[MAXN];
 
void Write(const int &Node) {
    if(Father[Node])
        Write(Father[Node]);
    fout << digit[Node];
}
 
int main() {
    int T;
    fin >> T;
    while(T -- ) {
        int N, P;
        fin >> N >> P; /// care dau restul N la impartirea cu P
        digits.clear();
        digits.insert(2%P);
        digits.insert(3%P);
        digits.insert(5%P);
        digits.insert(7%P);
        memset(Father, -1, sizeof(Father));
        for(set <int> :: iterator it = digits.begin(), fin = digits.end(); it != fin ; ++ it) {
            Q.push(*it);
            Father[*it] = 0;
            digit[*it] = *it;
        }
        while(!Q.empty()) {
            int Number = Q.front();
            Q.pop();
            for(set <int> :: iterator it = digits.begin(), fin = digits.end(); it != fin ; ++ it) {
                int actNumber = (Number * 10 + *it) % P;
                if(Father[actNumber] == -1) {
                    Father[actNumber] = Number;
                    digit[actNumber] = *it;
                    Q.push(actNumber);
                }
            }
        }
        if(Father[N] == -1) {
            fout << "-1\n";
            continue;
        }
        Write(N);
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
