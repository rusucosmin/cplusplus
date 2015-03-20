#include <iostream>
#include <fstream>
#define DN 2000000
using namespace std;

int n,t,b[DN],d[DN];
long long sol,sum;

int main()
{
    ifstream f("raliu.in");
    ofstream g("raliu.out");
    int start;
    for(f>>t; t;--t) {
        f>>n;
        for(int i=1; i<=n; ++i) f>>b[i];
        for(int i=1; i<=n; ++i) f>>d[i];

        sol=sum=0;
        for(int i=1; i<=n; ++i) sol+=b[i]-d[i];
        if(0>sol) {
            g<<"NU\n";
            continue;
        }
        start=1;
        for(int i=1; i<=n; ++i) {
            sum+=b[i]-d[i];
            if(0>sum) {
                sum=0;
                start=i+1;
            }
        }
        g<<"DA\n"<<start<<'\n';
    }
    return 0;
}
