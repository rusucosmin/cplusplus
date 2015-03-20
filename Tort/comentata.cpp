#include <fstream>
 
using namespace std;
 
//Acest tip de date va retine un numar mare
struct mare
{
    int v[30];
};
 
//Initializam marimea si primele n-1 cifre ale lui a cu 0
void init(mare &a,int n)
{
    int i;
 
    for(i=0;i<n;i++)
        a.v[i]=0;
}
 
//Functia intoarce produsul a doua numere mari
mare produs(mare a,mare b)
{
    mare aux;
    init(aux,30);
 
    //Matematic, lungimea produsului va fi a.v[0]+b.v[0] (sau a.v[0]+b.v[0]-1)
    aux.v[0]=a.v[0]+b.v[0];
 
    int i,j;
    for(i=1;i<=a.v[0];i++)
        for(j=1;j<=b.v[0];j++)
            aux.v[i+j-1]+=(a.v[i]*b.v[j]);
 
    for(i=1;i<=aux.v[0];i++)
    {
        aux.v[i+1]+=(aux.v[i]/10);
        aux.v[i]%=10;
    }
 
    while(aux.v[aux.v[0]]==0)
        aux.v[0]--;
 
    return aux;
}
 
//Functia returneaza maximul dintre a si b
int maxim(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
 
//Functia intoarce suma a+b
mare suma(mare a,mare b)
{
    mare aux;
    init(aux,30);
 
    aux.v[0]=max(a.v[0],b.v[0])+1; //Lungimea se va scadea la sfarsit daca este prea mare
 
    int i,transport=0;
 
    for(i=1;i<=aux.v[0];i++)
    {
        aux.v[i]=a.v[i]+b.v[i]+transport;
 
        if(aux.v[i]>9)
        {
            transport=1;
            aux.v[i]%=10;
        }
        else
            transport=0;
    }
 
    while(aux.v[aux.v[0]]==0)
        aux.v[0]--;
 
    return aux;
}
 
//Functia initializeaza un numar mare cu scalarul n
void init_scalar(mare &a,int n)
{
    init(a,30);
 
    while(n>0)
    {
        a.v[++a.v[0]]=(n%10);
        n/=10;
    }
}
 
//Deschiderea fisierelor de intrare si iesire
ifstream fin("tort.in");
ofstream fout("tort.out");
 
//Functia afiseaza un numar mare a
void afis(mare a)
{
    int i;
 
    for(i=a.v[0];i>=1;i--)
        fout<<a.v[i];
    fout<<'\n';
}
 
int main()
{
    mare fa1,fa2,fa3,fb1,fb2,fb3;
 
    init(fa1,30);
    init(fa2,30);
    init(fa3,30);
    init(fb1,30);
    init(fb2,30);
    init(fb3,30);
 
    //A-ul si B-ul din enunt
    int a,b;
 
    fin>>a;
    fin>>b;
 
    //Se calculeaza in t raspunsul (((a+1)*(a+2))/2)*(b+1)+(((b*(b+1))/2)*(a+1))
    if(a%2==1)
    {
        init_scalar(fa1,(a+1)/2);
        init_scalar(fa2,(a+2));
    }
    else
    {
        init_scalar(fa1,(a+1));
        init_scalar(fa2,(a+2)/2);
    }
 
    init_scalar(fa3,(b+1));
 
    if(b%2==1)
    {
        init_scalar(fb1,(b+1)/2);
        init_scalar(fb2,b);
    }
    else
    {
        init_scalar(fb1,(b+1));
        init_scalar(fb2,(b/2));
    }
 
    init_scalar(fb3,(a+1));
 
    mare t1,t2,t;
 
    init(t1,30);
    init(t2,30);
    init(t,30);
 
    t1=produs(produs(fa1,fa2),fa3);
    t2=produs(produs(fb1,fb2),fb3);
 
    //Se calculeaza si afiseaza raspunsul final
    t=suma(t1,t2);
    afis(t);
 
    //Inchiderea fisierelor de intrare si iesire
    fin.close();
    fout.close();
    return 0;
}
