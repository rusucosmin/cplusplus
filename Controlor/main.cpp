#include <iostream>
#include <fstream>
#define DN 1005
using namespace std;

int n,m[DN][DN],rez[DN][DN],sp[DN][DN];

FILE* fin=fopen("controlor.in","r");
const unsigned maxb=100;
char buf[maxb];
unsigned ptr=maxb;

inline unsigned getInt(){
    unsigned nr=0;
    while(buf[ptr]<'0'||'9'<buf[ptr])
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    while('0'<=buf[ptr]&&buf[ptr]<='9'){
            nr=nr*10+buf[ptr]-'0';
            if(++ptr>=maxb)
                    fread(buf,maxb,1,fin),ptr=0;
    }
    return nr;
}

int main()
{
    ifstream f("controlor.in");
    ofstream g("controlor.out");
    n = getInt();
    for(int i=1; i<n; ++i) for(int j=i+1; j<=n; ++j) m[i][j] = getInt();
    for(int i=1; i<=n; ++i) for(int j=i+1; j<=n; ++j)
        sp[i][j]=m[i][j]+sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1];
    for(int i=1; i<n; ++i) {
        for(int j=i+1; j<=n; ++j) {
            rez[i][j]=sp[j-1][n]-sp[i-1][n]-sp[j-1][j-1]+sp[i-1][j-1];
            g<<rez[i][j]<<' ';
        }
        g<<'\n';
    }
    return 0;
}
