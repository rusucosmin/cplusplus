#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int MAXN = 105;
 
char x[MAXN], y[MAXN];
int Q;
 
inline void divide(char *&s, int nb) {
    int r = 0;
    for(int i = *s ; i ; -- i) {
        *(s + i) = (r = 10 * r +(int) *(s + i)) / nb;
        r %= nb;
    }
    while(*s && !*(s + *s))
        -- *s;
}
 
inline int comp(char *s, char *p) {
    if(*s > *p)
        return 1;
    if(*s < *p)
        return 2;
    for(int i = (int) *s ; i ; -- i) {
        if(*(s + i) == *(p + i))
            continue;
        if(*(s + i) > *(p + i))
            return 1;
        else
            return 2;
    }
    return 0;
}
 
int main() {
    ifstream fin("easylca.in");
    ofstream fout("easylca.out");
    fin >> Q;
    while (Q --) {
        fin >> (x + 1) >> (y + 1);
        x[0] = strlen(x + 1);
        y[0] = strlen(y + 1);
        for(int i = 1 ; i <= x[0] ; ++ i)
            x[i] -= '0';
        for(int i = 1 ; i <= y[0] ; ++ i)
            y[i] -= '0';
        reverse(x + 1, x + x[0] + 1);
        reverse(y + 1, y + y[0] + 1);
        char *s = x;
        char *p = y;
        int ans = 0;
        while(ans = comp(s, p)) {
            if(ans == 1)    
                divide(s, 2);
            else
                divide(p, 2);
        }
        for(int i = *s ; i ; -- i) 
            fout << (int) *(s + i);
        fout << '\n';
             
         
    }
 
}
