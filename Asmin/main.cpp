/* Mugurel Ionut Andreica - Bucuresti, ROMANIA */

/* Time Complexity: O(N) */

#include <stdio.h>
#include <string.h>
#define maxn 1001
#define filein "asmin.in"
#define fileout "asmin.out"

typedef struct nod
{
    long x;
    nod *urm;
} *pnod;

pnod edge[maxn],aux;
long v[maxn],marc[maxn],minim[maxn],tata[maxn];
long i,j,k,n,root,sum,needed,min,nsol=0,modulo;

void read();
void compute();
void print();
void df(long);
void df2(long);
long extra(long,long);

int main()
{
    read();
    compute();
    print();
    return 0;
}

void read()
{
    freopen(filein,"r",stdin);
    scanf("%ld %ld",&n,&modulo);

    for (i=1; i<=n; i++)
        edge[i]=NULL;

    for (k=1; k<n; k++)
    {
        scanf("%ld %ld",&i,&j);

        aux=new nod;
        aux->x=j;
        aux->urm=edge[i];
        edge[i]=aux;

        aux=new nod;
        aux->x=i;
        aux->urm=edge[j];
        edge[j]=aux;
    }

    for (i=1; i<=n; i++)
        scanf("%ld",&v[i]);
}

void compute()
{
    memset(marc,0,sizeof(marc));
    df(1);

    minim[1]=min=needed;

    memset(marc,0,sizeof(marc));
    df2(1);
}

void print()
{
    freopen(fileout,"w",stdout);

    for (i=1,nsol=0; i<=n; i++)
        if (minim[i]==min)
            nsol++;

    printf("%ld %ld\n",min,nsol);

    k=1;
    for (i=1; i<=n; i++)
        if (minim[i]==min)
        {
            if (!k) printf(" ");
            printf("%ld",i);
            k=0;
        }

    printf("\n");
}

void df(long nod)
{
    pnod aa=edge[nod];
    long i,suminit=sum;

    marc[nod]=1;

    needed+=extra(sum,v[nod]);
    sum=v[nod];

    aa=edge[nod];
    while (aa!=NULL)
    {
        i=aa->x;

        if (!marc[i])
            df(i);

        aa=aa->urm;
    }

    sum=suminit;
}

void df2(long nod)
{
    pnod aa=edge[nod];
    long i,suminit=sum;

    marc[nod]=1;
    aa=edge[nod];
    while (aa!=NULL)
    {
        i=aa->x;

        if (!marc[i])
        {
            minim[i]=minim[nod]-v[nod]-extra(v[nod],v[i])
                     +v[i]+extra(v[i],v[nod]);

            if (minim[i]<min)
                min=minim[i];

            df2(i);
        }

        aa=aa->urm;
    }
}

long extra(long v1,long v2)
{
    if (v1<=v2)
        return (v2-v1);
    else
        return (modulo-v1+v2);
}
