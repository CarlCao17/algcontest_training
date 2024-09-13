//
// Created by 曹正盛 on 24-8-10.
//
#include<cstdio>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int x = (4*n-m)/2, y = n - x;
    if ((m & 1) == 1|| x < 0 || y < 0) {
        printf("No answer\n");
    } else {
        printf("鸡的数量 = %d, 兔的数量 = %d\n", x, y);
    }
}
