#include <iostream>
#include <math.h>
using namespace std;

int noOfDigits(long long n) {
	if(n == 0)
		return 0;
    int ans=0;
    while (n>0) {
    	n /= 10;
    	ans += 1;
    }
    return ans;
}

long long lastDigitsExceptFirst(long long N, int len, int MSB) {
    long long ans = N - MSB * (pow(10, len-1));
    return ans;
}

long long minNoOfSteps(int N) {
    if (N == 0)
        return 0;
    if (N == 1)
        return 0;
    if (N == 2)
        return 10;
    if (N >= 3) {
        long long ans = 10;
        ans = ans + (N - 2) * 9LL;
        for (int i = 1; i <= N - 2; ++ i)
            ans = ans + pow(10, i);
        return ans;
    }
}


int main()
{
    freopen("codejam1balarge.in", "r", stdin);
    freopen("codejam1balarge.out", "w", stdout);
    int t, i;
    scanf("%d",&t);
    for (i = 1; i <= t; i++) {
        long long ans, N;
        scanf("%lld",&N);
        int len = noOfDigits(N);
        long long noOfSteps = minNoOfSteps(len);
        int MSB = N/pow(10, len-1);
        long long digitsExceptMSB = lastDigitsExceptFirst(N, len, MSB);
        if (N <= 10)
            ans = N;
        else if (MSB == 1)
            ans = noOfSteps + digitsExceptMSB;
        else if (MSB != 1)
            ans = noOfSteps + MSB + digitsExceptMSB;
        printf("Case #%d: %lld\n",i,ans);
    }
    return 0;
}
