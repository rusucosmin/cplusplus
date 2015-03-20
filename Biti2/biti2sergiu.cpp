#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#define base 10
#define E (1<<15)
using namespace std;
 
typedef int Huge[2600];
 
int countBits(int x) {
    int count = 0;
    while(x != 0) {
        count++;
        x = x & (x-1);
    }
    return count;
}
 
void transform(Huge A, string s) {
    int a = int(s.size())-1, b = int(s.size())-1;
    memset(A, 0, int(s.size()+1)*sizeof(int));
 
    while(b >= 0) {
        A[0]++;
        for(int i=max(a, 0); i<=b; i++) A[A[0]] = A[A[0]] * 10 + int(s[i]) - 48;
        b = a - 1;
        a = b;
    }
    while(A[0] && A[A[0]] == 0) A[0]--;
}
 
void div(Huge A, int digit) {
    int R = 0;
    for(int i=A[0]; i>=1; i--) {
        A[i] = (R = base * R + A[i]) / digit;
        R %= digit;
    }
    while(A[0] && A[A[0]] == 0) A[0]--;
}
 
int mod(Huge A, int digit) {
    int R = 0;
    for(int i=A[0]; i; i--) R = (base * R + A[i]) % digit;
    return R;
}
 
int bit(Huge pos) {
    if(pos[0] == 0 || (pos[0] == 1 && pos[1] == 0)) return 0;
 
    int ret = 0;
 
    while(pos[0]) {
        ret += countBits(mod(pos, E));
        div(pos, E);
    }
 
    return (ret%2);
}
 
 
int main() {
    ifstream f("biti2.in");
    ofstream g("biti2.out");
 
    int T;
    string line;
    Huge X;
 
    f>>T;
    f.get();
    while(T--) {
        getline(f, line);
        transform(X, line);
        //cout<<X[0]<<" "<<X[1]<<"\n";
        g<<bit(X)<<"\n";
    }
 
    return 0;
}
