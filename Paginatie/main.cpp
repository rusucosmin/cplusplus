#include<fstream>
#include<string.h>
using namespace std;

ifstream cin("paginatie.in");
ofstream cout("paginatie.out");
char a[55], b[55];
long long nr_col, nr_linii, l, s, nr;
int main()
{
    cin>>nr_col>>nr_linii;
    cin>>a;
    //cout<<a<<" ";
    //cout<<b<<" ";
    while(cin>>b)
    {
        l=strlen(a);
        s+=l;
        if(s<nr_linii && s+strlen(b)<nr_linii)
        {
            cout<<a<<" ";
            s++;
        }
        else {
            if(s<nr_linii)
                for (long long j=1;j<=nr_linii-s;j++)
                    cout<<" ";
            cout<<a<<"\n";
            nr++;
            s=0;
            }
        if(nr==nr_col)
            {
                cout<<"\n";
                nr=0;
            }
        memcpy(a,b,sizeof(a));
        memset(b,0,sizeof(b));
    }

    l=strlen(a);
    s+=l;
    if (s<nr_linii&&s+strlen(b)<nr_linii)
    {
        cout<<a<<" ";
        s++;
    }
    else
    {
        if (s<nr_linii)
        for (long long j=1;j<=nr_linii-s;j++)
            cout<<" ";
        cout<<a<<"\n";
        nr++;
        s=0;
    }
    if (nr==nr_col)
    {
        cout<<"\n";
        nr=0;
    }
    return 0;
}
