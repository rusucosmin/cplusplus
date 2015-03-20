#include<fstream>
#include<stdio.h>
#include<algorithm>
using namespace std;
int n, a[100001];
int A,B,c,i,j, ch, hg, poz;
void cit ( int &x ) {
    if ( a[0] == '\0' ) fread ( a, 1, hg, stdin ) ;
    else
        while (a[poz] < '0' || a[poz] > '9')
            if (++poz == hg) fread (a, 1, hg, stdin), poz = 0;
    x = 0;
    while (a[poz] >= '0' && a[poz] <= '9') {
        x = x * 10 + a[poz] - '0';
        if (++poz == hg) fread (a, 1, hg, stdin), poz = 0;
    }
}
int caz1(int b, int li)
{
    int  ls=n, mij, fin;
    while( li<=ls)
    {
        mij=(li+ls)/2;
        if (a[mij]<=b)
        {
            fin=mij;
            li=mij+1;
        }
        else
            ls=mij-1;
    }
    return fin;
}

int caz2(int b, int li)
{
    int ls=n,mij,fin;
    while(li<=ls)
    {
    mij=(li+ls)/2;
    if (a[mij]>=b)
    {
        fin=mij;
        ls=mij-1;
    }
    else
    li=mij+1;
    }
    return fin;
}
int cmp(long a, long b)
{
    if(a<b) return 1;
    else return 0;
    return 0;
}
int main()
{
    freopen("teams.in", "r", stdin);
freopen("teams.out", "w", stdout);
scanf("%ld%ld%ld",&n,&A,&B);
    cit(n);
    //cin>>n>>A>>B;
 //   for(i=1;i<=n;i++)
   // scanf("%ld",&a[i]);
   // cin.close();
  //  quickSort(a, 1, n);
  sort(a+1, a+n+1, cmp);
    for(i=1;i<n;i++)
       if(a[i]+a[i+1]<=B) { //cout<<a[i]<< " "<<caz1(B-a[i], i+1)-caz2(A-a[i], i+1);
     c+=caz1(B-a[i], i+1)-caz2(A-a[i], i+1)+1 ;}
       printf("%ld", c);
 //   cout<<c;
//    cout.close();
    return 0;
}
