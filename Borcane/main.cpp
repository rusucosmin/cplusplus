#include<fstream>
#include<math.h>
#include<stdlib.h>
using namespace std;
ifstream fin("borcane.in");
ofstream fout("borcane.out");
struct vector
{
 long val,l;
};
long n,i,j,l,ok,s;
vector v[101],x[101];
int comp(const void *a,const void *b)
{
 if(*(long *)a> *(long *)b)
  return 1;
 else
  return -1;
}
int main()
{
 fin>>n;
 for(i=1;i<=n;i++)
 {
  fin>>v[i].val;
                v[i].l=i;
 }
 qsort(v+1, n , sizeof(v[0]), comp);
 i=1;
 while(i<n)
        {
  while(v[i].val)
  {
   v[n].val+=2;
   v[i].val--;
   v[i+1].val--;
   fout<<v[i].l<<v[i+1].l<<v[n].l<<endl;
  }
  i++;
        }
 return 0;
}
