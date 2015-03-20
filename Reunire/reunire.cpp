#include<fstream>
using namespace std;

long long x11,y11,x12,y12,x21,y21,x22,y22,x31,y31,x32,y32;
int ok1,ok2,ok3,k;
long long a[6],p[6],aria,perim;


void calcul(long long x11,long long y11,long long x12,long long y12,long long x21,long long y21,long long x22,long long y22)
{
 long long xi1,yi1,xi2,yi2;
	
 xi1=max(x11,x21); yi1=max(y11,y21);
 xi2=min(x12,x22); yi2=min(y12,y22);
 
 if (xi2>=xi1 && yi2>=yi1)
	 {
	  a[k]=(xi2-xi1) * (yi2-yi1);
	  p[k]=(xi2-xi1)*2 + (yi2-yi1)*2; 
	 } else
	 {
	  p[k]=0;
	  a[k]=0;
	 }
}


void calculinter()
{
 long long xi1,yi1,xi2,yi2;
	
 xi1=max(max(x11,x21),x31); yi1=max(max(y11,y21),y31);
 xi2=min(min(x12,x22),x32); yi2=min(min(y12,y22),y32);
 
 if (xi2>=xi1 && yi2>=yi1)
	 {
	  a[k]=(xi2-xi1) * (yi2-yi1);
	  p[k]=(xi2-xi1)*2 + (yi2-yi1)*2; 
	 } else
	 {
	  p[k]=0;
	  a[k]=0;
	 }
}


int main()
{
	
 ifstream fin("reuniune.in");
 fin>>x11>>y11>>x12>>y12;
 fin>>x21>>y21>>x22>>y22;
 fin>>x31>>y31>>x32>>y32;
 
 k=1;
 calcul(x11,y11,x12,y12,x21,y21,x22,y22);
 k=2;
 calcul(x11,y11,x12,y12,x31,y31,x32,y32);
 k=3;
 calcul(x31,y31,x32,y32,x21,y21,x22,y22);
 k=4;
 calculinter();
 
 aria=(x12-x11)*(y12-y11) + (x22-x21)*(y22-y21) + (x32-x31)*(y32-y31) - a[1] - a[2] - a[3] + a[4]; 
 perim=(x12-x11)*2+(y12-y11)*2 + (x22-x21)*2+(y22-y21)*2 + (x32-x31)*2+(y32-y31)*2 - p[1] - p[2] - p[3] + p[4]; 
 
 ofstream fout("reuniune.out");
 fout<<aria<<" "<<perim;

 fin.close();
 fout.close(); 
 
 return 0;
}
