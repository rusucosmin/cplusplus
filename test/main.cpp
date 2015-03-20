#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void minimum_coins(const vector<int> &v, int e) {
    // Write your code here
    // To print results to the standard output you can use the cout stream
    // Example: cout << "Hello world!";
    vector <int> dp(e + 1, numeric_limits<int>::max()); /// dp[i] = min number of coins witch sum up to i
    dp[0] = 0;
    for(int i = 1 ; i <= e ; ++ i)
        for(int j = 0 ; j < v.size() ; ++ j)
            if(i - v[j] >= 0)
                dp[i] = min(dp[i], dp[i - v[j]] + 1);
    cout << dp[e] << '\n';
}
