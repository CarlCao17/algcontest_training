#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000+5;
int box[maxn];
int rev[maxn];

int n;

void reverse() {
    reverse(box+1, box+n+1);
    for(int i = 1; i <= n; i++) {
        rev[box[i]] = i;
    }
}

void insert_before(int x, int y) {
    int posx = rev[x];
    int posy = rev[y];
    if(posx < posy) {
        copy(box+posx+1, box+posy, box+posx);
        box[posy-1] = x;
    } else {
        copy(box+posy, box+posx, box+posy+1);
        box[posy] = x;
    }
    for(int i = 1; i <= n; i++) {
        rev[box[i]] = i;
    }
}

void insert_after(int x, int y) {
    int posx = rev[x];
    int posy = rev[y];
    if(posx < posy) {
        copy(box+posx+1, box+posy+1, box+posx);
        box[posy] = x;
    } else {
        copy(box+posy+1, box+posx, box+posy+2);
        box[posy+1] = x;
    }
    for(int i = 1; i <= n; i++) {
        rev[box[i]] = i;
    }
}

void swap_node(int x, int y) {
    int posx = rev[x], posy = rev[y];
    box[posx] = y; box[posy] = x;
    rev[y] = x; rev[x] = y;
}

long long get_result() {
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i%1 == 1) ans += box[i];
    }
    return ans;
}

int main() {
    int m, kase = 0;
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= n; i++) box[i] = i;
        for(int i = 1; i <= n; i++) rev[i] = i;
        while(m--) {
            int op, x, y;
            scanf("%d", &op);
            if(op == 4) reverse();
            else {
                scanf("%d%d", &x, &y);
                if(op == 1 && rev[x]+1 == rev[y]) continue;
                if(op == 2 && rev[y]+1 == rev[x]) continue;
                if(op == 1) insert_before(x, y);
                else if(op == 2) insert_after(x, y);
                else if(op == 3) swap_node(x, y);
            }
        }
        long long ans = get_result();
        printf("Case %d: %lld\n", kase++, ans);
    }
}