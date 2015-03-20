/*
    Solutie prof. Silviu Candale
*/
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>
#define NN 1000
//#define DEBUG
using namespace std;

ifstream fin("compresie.in");
ofstream fout("compresie.out");

int n;
char s[NN*NN+10], a[NN+2][NN+2];
int poz;
int cifra(char c){
	return c>='0' && c<='9';
}

void reconstituire(int i1,int j1, int i2, int j2){
	if(i1>i2 || j1>j2)
		return;
	if(s[poz] == '*'){
		int mi=(i1+i2)/2, mj=(j1+j2)/2;
		poz++;
		reconstituire(i1 ,j1 ,mi ,mj);
		reconstituire(i1 , mj+1 , mi , j2);
		reconstituire(mi+1 , j1 , i2 , mj);
		reconstituire(mi+1 , mj+1 , i2 , j2);
	}
	else{
		while( cifra(s[poz]) )
			++poz;
		for(int i=i1 ; i<=i2 ; ++i)
			for(int j=j1 ; j<=j2 ; ++j)
				a[i][j]=s[poz];
		++poz;
	}
}

int main(){
	fin.getline(s,NN*NN+5);
	//
	int taieturi = 0,in_numar = 0,x = 0, np=0;
	for(int i=0;s[i];++i)
		if(s[i]=='*')
			++taieturi;
		else{
			if(cifra(s[i]))
				if(in_numar)
					x = 10 * x + s[i]-'0';
				else
					x=s[i]-'0' , in_numar = 1;
			else{
				np += x;
				x = 0;
				if(s[i]>='a' && s[i]<='z' && !cifra(s[i-1]) )
					np++;
			}
		}
	#ifdef DEBUG
		cout << np << endl;
	#endif
	n = (int)sqrt((double)np);
	fout << taieturi <<"\n";
	reconstituire(1,1,n,n);
	for(int i=1 ; i<=n ; ++i){
		for(int j=1 ; j<=n ; ++j)
			fout << a[i][j];
		fout << endl;
	}
}


