#include<cstdio>
#include<cstring>
#define N 1000
int main() {
    int n;
    char puzzle[N], guess[N];
    int cnt[26];

    while(scanf("%d", &n) && n > 0) {
        int left_wrong_num = 7;
        int left = 0;
        memset(cnt, 0, sizeof(cnt));
        scanf("%s%s", puzzle, guess);
        for(int i = 0; puzzle[i]!='\0'; i++) {
            if(cnt[puzzle[i]-'a'] == 0) ++left;
            ++cnt[puzzle[i]-'a'];
        }
        for(int i = 0; guess[i]!='\0'; i++) {
            if(cnt[guess[i]-'a'] > 0) {
                cnt[guess[i]-'a'] = 0;
                left--;
                if(left == 0) break;
            } else {
                left_wrong_num--;
                if(left_wrong_num == 0) break;
            }
        }
        printf("Round %d\n", n);
        if(left == 0) printf("You win.\n");
        else if(left_wrong_num == 0) printf("You lose.\n");
        else printf("You chickened out.\n");
    }

    return 0;
}