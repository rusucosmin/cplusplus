#include <fstream>
#include<string.h>
using namespace std;
ifstream cin("par.in");
ofstream cout("par.out");
char st[5005];
int i, j, n,u, sol, paranteze_deschise, paranteze_inchise;
char s[5005];
int main()
{
	    cin>>n;
		    if(n%2==1)
			       {cout<<"-1";
				          return 0;}
						      cin.getline(st, 1000);
							      cin.getline(s,50005);
								      for(i=0;i<n;i++)
									        {
												 
												        if(s[i]==')')
														        {if(paranteze_deschise!=0)
																              paranteze_deschise--;
																			               else paranteze_inchise++;
																						                }
																										        else   paranteze_deschise++;
																												 
																												       }
																													         if((paranteze_deschise)%2==0 && (paranteze_inchise)%2==0)
																															             cout<<(paranteze_deschise+paranteze_inchise)/2;
																																		       else cout<<(paranteze_deschise-1)/2+(paranteze_inchise-1)/2+2;
																																			       return 0;
																																				   }
											

