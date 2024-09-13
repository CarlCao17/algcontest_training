//
// Created by 曹正盛 on 24-8-11.
//
#include<cstdio>
#include<cmath>
void print_aabb() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            int num = a*1100+b*11;
            int x = int(sqrt(num));
            if (x*x == num) {
                printf("%d\n", num);
            }
        }
    }
}

int main() {
    print_aabb();
}
