#include<cstdio>

int main() {
    int kase;
    int D, I;
    scanf("%d", &kase);
    while(kase--) {
        scanf("%d%d", &D, &I);
        int k = 1;
        for(int i = 0; i < D-1; i++) {
            if(I%2) { k *= 2; I = (I+1)/2; }
            else { k = 2*k+1; I /= 2;}
        }
        printf("%d\n", k);
    }
}