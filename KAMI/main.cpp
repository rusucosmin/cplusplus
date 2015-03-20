#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long int lld;
const int NMAX = 100000+2;
const int LMAX = 317+5;
const lld INF = (1LL<<62);

int N,M,P;
lld Q;
int A[NMAX];
lld S[NMAX],TS;
lld B[NMAX];
lld AIB[NMAX];
int Desc[LMAX];
lld Lazy[LMAX];

void upd_aib(int x,lld val)
{
    int i;
    for(i=x; i<=N; i+=i&(-i))
        AIB[i]+=val;
}

lld qry_aib(int x)
{
    int i;
    lld ans=0;
    for(i=x; i; i-=i&(-i))
        ans+=AIB[i];
    return ans;
}

int Query(int R)
{
    int i,l,r;
    r=(R-1)/P+1;

    for(i=R-1; i>=(r-1)*P+1; i--)
        if(B[i]+Lazy[r] >= Q) return i;

    for(i=r-1; i>=1; i--)
        if(B[Desc[i]]+Lazy[i] >= Q) break;

    l=i;
    for(i=min(R-1,l*P); i>=max(1,(l-1)*P+1); i--)
        if(B[i]+Lazy[l] >= Q) break;
    return i;
}

void Update(int x,int val)
{
    int i,p=(x-1)/P+1;
    lld dif=val-A[x];

    A[x]+=dif;
    B[x]+=dif;
    TS+=dif;
    upd_aib(x,dif);
    Desc[p]=x;

    for(i=(p-1)*P+1; i<=x-1; i++)
    {
        B[i]-=dif;
        if(B[i]>=B[Desc[p]]) Desc[p]=i;
    }
    for(i=x+1; i<=min(N,p*P); i++)
        if(B[i]>=B[Desc[p]]) Desc[p]=i;

    for(i=1; i<p; i++)
        Lazy[i]-=dif;
}

int main()
{
    int i,t,x,p;

    freopen("kami.in","r",stdin);
    freopen("kami.out","w",stdout);

    scanf("%d",&N);

    for(i=1; i<=N; i++)
    {
        scanf("%d",&A[i]);
        upd_aib(i,A[i]);
        TS+=A[i];
    }

    for(P=1; P*P<=N; P++);

    S[N]=A[N];
    B[0]=B[N]=-INF;

    for(i=N-1; i>=1; i--)
    {
        S[i]=S[i+1]+A[i];
        B[i]=A[i]-S[i+1];
        p=(i-1)/P+1;
        if(B[Desc[p]] < B[i]) Desc[p]=i;
    }

    scanf("%d",&M);

    for(; M; --M)
    {
        scanf("%d",&t);
        if(t==1)
        {
            scanf("%d",&x);
            Q=-(TS-qry_aib(x));
            printf("%d\n",Query(x));
            continue;
        }
        scanf("%d%d",&x,&t);
        Update(x,t);
    }

    return 0;
}
