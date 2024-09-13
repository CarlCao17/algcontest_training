//
// Created by 曹正盛 on 24-8-10.
//
#include<cstdio>
#define N 1000

int get_digits(const long n, char* digits) {
    long q = n, r = 0;
    int cnt = 0;
    while (q > 0) {
        long t = q / 10;
        r = q - 10 * t;
        q = t;
        digits[cnt++] = char(r);
    }
    return cnt;
}

long compose_to_number(const char* digits, int n) {
    long res = 0;
    for (int i = 0; i < n; i++) {
        res = res * 10 + digits[i];
    }
    return res;
}

int main() {
    long num;
    char digits[N];
    scanf("%ld", &num);
    int n = get_digits(num, digits);
    printf("%ld\n", compose_to_number(digits, n));
}
