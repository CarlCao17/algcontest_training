//
// Created by 曹正盛 on 24-8-11.
//
#include<cstdio>
#define N 10000
int table[N+1];

int cal(int n) {
    int cnt = 0;
    while (n > 1) {
        if ((n & 1) == 1) n = 3 * n + 1;
        else n /= 2;
        cnt++;
    }
    return cnt;
}

void pre_calculate() {
    for (int i = 1; i <= N; i++) {
        table[i] = cal(i);
    }
}

int solve(int n) {
    if (n <= N) return table[n];
    return cal(n);
}

int main() {
    pre_calculate();


    int num = 0;
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        int n;
        scanf("%d", &n);
        int cnt = solve(n);
        printf("%d\n", cnt);
    }
}