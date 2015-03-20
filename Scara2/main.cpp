#include <fstream>
#include <iomanip>
#define InFile "scara2.in"
#define OutFile "scara2.out"
#define NMax 10
#define HMax 78
using namespace std;
short sol[NMax], solmin[NMax], uz[HMax], htot;
double ef[NMax], efmin;
//ef[i]=efortul minim cu care urc primele i trepte din sol
short N, H, p, M;

void Citire();
void Gen(int k);
void Afisare();
double efort ();
int main()
{
     Citire();
     efmin=(double)H*N+1;
     Gen(1);
     Afisare();
     return 0;
}
void Citire()
{
     ifstream fin(InFile);
     fin>>H>>N>>M>>p;
     fin.close();
}
void Afisare()
{
     int i;
     ofstream fout(OutFile);
     fout<<fixed<<setprecision(2)<<efmin<<"\n";
     for (i=1; i<N; i++)
         fout<<solmin[i]<<' ';
     fout<<solmin[N]<<"\n";
     fout.close();
}
double efort()
{
int k, j;
double x, sum;
 for (k=1; k<=N; k++)
    {x=sol[k]+ef[k-1];//urc cu efort minim primele k-1 trepte si apoi urc treapta k de inaltime i
     sum=sol[k];
     for (j=2; k-j>=0; j++)
         {//urc deodata j trepte k, k-1, ..., k-j+1, daca suma inaltimilor lor este <=M
          //in sum calculez suma inaltimilor
          sum+=sol[k-j+1];
          if (sum>M) break;
          if (((sum/j)+p+ef[k-j])<x)
              x=((sum/j)+ef[k-j]+p);
          }
     ef[k]=x;
    }
 return ef[N];
}
void Gen(int k)
{
     int i;
     double x;
     if (k==N+1)
     {
      if (htot==H)
       {
              x=efort();
              if (x<efmin && efmin-x>0.001)
              {
                 efmin=x;
                 for (i=1; i<=N; i++) solmin[i]=sol[i];
              }
       }
     }
   else
   for (i=1; i<=H && htot+i<=H && i<=M; i++)
       if (!uz[i])
          {
          //care ar fi efortul minim daca as pune inaltimea treptei k=i?
               sol[k]=i; htot+=i; uz[i]=1;
               Gen(k+1);
               uz[i]=0; htot-=i;
          }
}
