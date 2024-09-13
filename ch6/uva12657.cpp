#include<cstdio>
#include<algorithm>

const int maxn = 100000+5;
int left[maxn], right[maxn];

void link(int L, int R) {
    right[L] = R; left[R] = L;
}

int main() {
    int kase = 0;
    int n, m;
    while(scanf("%d%d", &n, &m) == 2) {
        int op, X, Y;
        int inv = 0;
        for(int i = 1; i <= n; i++) {
            left[i] = i-1;
            right[i] = i+1;
        }
        right[n] = 0;
        left[0] = n; right[0] = 1;

        while(m--) {
            scanf("%d", &op);
            if(op == 4) inv = !inv;
            else {
                scanf("%d%d", &X, &Y);
                if(inv && op < 3) op = 3 - op;
                if(op == 1 && left[Y] == X) continue;
                if(op == 2 && right[Y] == X) continue;

                int LX = left[X], RX = right[X], LY = left[Y], RY = right[Y];
                if(op == 3) {
                    if(right[Y] == X) std::swap(X, Y);
                    if(right[X] == Y) { link(LX, Y); link(Y, X); link(X, RY);}
                    else { link(LX, Y); link(Y, RX); link(LY, X); link(X, RY); }
                } else if(op == 1) {
                    link(LX, RX); link(LY, X); link(X, Y);
                } else if(op == 2) {
                    link(LX, RX); link(Y, X); link(X, RY);
                }
            }
        }

        long long res = 0;
        int b = 0;
        for(int i = 1; i <= n; i++) {
            b = right[b];
            if((i&1) == 1) res += b;
        }
        if(inv && (n&1) == 0) res = (long long)n*(n+1)/2 - res;
        printf("Case %d: %lld\n", ++kase, res);
    }
    return 0;
}