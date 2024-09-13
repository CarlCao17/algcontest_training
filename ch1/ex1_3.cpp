//
// Created by 曹正盛 on 24-8-10.
//
#include<cstdio>
#include"../utility.h"


int main() {
    long a, b;
    scanf("%ld%ld", &a, &b);
    swap(&a, &b);
    printf("%ld %ld", a, b);
}
