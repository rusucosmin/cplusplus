#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {
    const char decision_string[2][11]={"IMPOSSIBLE", "POSSIBLE"};
    int T, B, decision;
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    scanf("%d", &T);
    long long M;
    for(int T_i = 1; T_i <= T; T_i++) {
        scanf("%d %lld", &B, &M);
        decision = (((long long)1)<<(B-2) >= M);

        printf("Case #%d: %s\n", T_i, decision_string[decision]);
        if (decision) {
            int connection[51][51]={};
            int complete_level;
            complete_level = log2(M);
            for (int i = B-complete_level-1; i < B; i++) {
                for (int j = i+1; j <= B; j++) {
                    connection[i][j] = 1;
                }
            }
            for (int i = 0; i <= complete_level && B-i-1>1; i++){
                if((1<<i)&M) {
                    connection[1][B-i-1] = 1;
                }
            }
            for(int i = 1; i <= B; i++) {
                for(int j = 1; j <= B; j++) {
                    printf("%d", connection[i][j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
