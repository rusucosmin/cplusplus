#include <fstream>
#include <string.h>
using namespace std;

ifstream cin("evaluare.in");
ofstream cout("evaluare.out");
char s[100005], op[100005];
int kp;
int fac[100005];
int vf;
char OP;
int op1, op2;
int main()
{
    cin.getline(s, 100002);
    for(int i=0; s[i] ; )
    {
        if(isdigit(s[i]))
        {
            fac[++vf]=s[i]-'0';
            while(isdigit(s[++i]))
                    fac[vf]=fac[vf]*10+s[i]-'0';
            continue;
        }
        if(s[i]=='(')
            {
                op[++kp]=s[i];
                i++;
                continue;
            }
        if(s[i]=='*')
            {
                //equal priority
                if(op[kp]=='*')
                   {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]*=op1;
                   }
                if(op[kp]=='/')
                    {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]/=op1;
                    }
                else op[kp]=s[i];
            }
        if(s[i]=='/')
            {
                if(op[kp]=='*')
                   {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]*=op1;
                   }
                if(op[kp]=='/')
                    {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]/=op1;
                    }
                else op[kp]=s[i];
            }
        if(s[i]=='+')
            {
                if(op[kp]=='+')
                   {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]+=op1;
                   }
                if(op[kp]=='-')
                    {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]-=op1;
                    }
                if(op[kp]=='*')
                    {
                        op1=fac[vf--];
                        fac[vf]*=op1;
                    }
                else if(op[kp]=='/')
                    {
                        op1=fac[vf--];
                        fac[vf]/=op1;
                    }
                else op[kp]=s[i];
                i++ ;continue;
            }
        if(s[i]=='-')
            {
                if(op[kp]=='+')
                   {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]+=op1;
                   }
                if(op[kp]=='-')
                    {
                        kp--;
                        op1=fac[vf--];
                        fac[vf]-=op1;
                    }
                if(op[kp]=='*')
                    {
                        op1=fac[vf--];
                        fac[vf]*=op1;
                    }
                else if(op[kp]=='/')
                    {
                        op1=fac[vf--];
                        fac[vf]/=op1;
                    }
                else op[kp]=s[i];
                i++ ;continue;
            }
        if(s[i]==')')
           {
                if(op[kp]=='(')
                    {
                        kp--;
                        ++i;
                        continue;
                    }
                else if(op[kp]=='*')
                    {
                        op1=fac[vf--];
                        fac[vf]*=op1;
                        --kp;
                    }
                else if(op[kp]=='/')
                    {
                        op1=fac[vf--];
                        fac[vf]/=op1;
                        --kp;
                    }
                else if(op[kp]=='+')
                    {
                        op1=fac[vf--];
                        fac[vf]+=op1;
                        --kp;
                    }
                else if(op[kp]=='-')
                    {
                        op1=fac[vf--];
                        fac[vf]-=op1;
                        --kp;
                    }
            }
        ++i;
    }
 // for(int i=1;i<=kp;++i)
  //      cout<<op[i];
    cout<<fac[1];
    cin.close();
    cout.close();
    return 0;
}
