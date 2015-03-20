#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
long long a[1013],crt,Min;
inline long long pow( int n)
{
    int i;
    long long nr=1;
    for (i=1; i<=n; i++)
        nr*=2;
    return nr;
}
int n;
int main()
{
    fstream f,g;
    f.open("hanoi4.in", ios::in);
    g.open("hanoi4.out", ios::out);
    f>>n;
    a[1]=1;
    a[2]=3;
    a[3]=5;
    int j,i;
    for (i=4; i<=n; i++)
    {
        Min=LONG_LONG_MAX;
        for (j=1; j<i; j++)
        {
            crt=a[j];
            if (i-j<50)
            {
                crt+=pow(i-j);
                crt=crt-1;
                crt+=a[j];
                if (crt<Min)
                    Min=crt;
            }
        }
        a[i]=Min;
    }
    g<<a[n];
}
