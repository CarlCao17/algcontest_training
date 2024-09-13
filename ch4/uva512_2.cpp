#include<cstdio>
#define maxd 10000

struct Command {
    char c[5];
    int r1, c1, r2, c2;
    int a, x[20];
} cmds[maxd];

int r, c, n;

int simulate(int& r0, int& c0) {
    for(int i = 0; i < n; i++) {
        Command &cmd = cmds[i];
        if(cmd.c[0] == 'E') {
            if(cmd.r1 == r0 && cmd.c1 == c0) { r0 = cmd.r2; c0 = cmd.c2; }
            else if(cmd.r2 == r0 && cmd.c2 == c0) { r0 = cmd.r1; c0 = cmd.c1; }
        } else {
            int dr = 0, dc = 0;
            for(int j = 0; j < cmd.a; j++) {
                int x = cmd.x[j];
                if(cmd.c[0] == 'I') {
                    if(cmd.c[1] == 'R' && x <= r0) dr++;
                    if(cmd.c[1] == 'C' && x <= c0) dc++;
                } else {
                    if(cmd.c[1] == 'R' && x == r0) return 0;
                    if(cmd.c[1] == 'C' && x == c0) return 0;
                    if(cmd.c[1] == 'R' & x < r0) dr--;
                    if(cmd.c[1] == 'C' && x < c0) dc--;
                }
            }
            r0 += dr; c0 += dc;
        }
    }
    return 1;
}

int main() {
    int kase = 0;

    while(scanf("%d%d%d", &r, &c, &n) == 3 && r) {
        for(int i = 0; i < n; i++) {
            Command &cmd = cmds[i];
            scanf("%s", &cmd.c);
            if(cmd.c[0] == 'E') scanf("%d%d%d%d", &cmd.r1, &cmd.c1, &cmd.r2, &cmd.c2);
            else {
                scanf("%d", &cmd.a);
                for(int j = 0; j < cmd.a; j++) scanf("%d", &cmd.x[j]);
            }
        }
        int q, r0, c0;
        if(kase > 0) printf("\n");
        printf("Spreadsheet #%d\n", ++kase);

        scanf("%d", &q);
        while(q--) {
            scanf("%d%d", &r0, &c0);
            printf("Cell data in (%d,%d) ", r0, c0);
            if(!simulate(r0, c0)) printf("GONE\n");
            else printf("moved to (%d,%d)\n", r0, c0);
        }
    }
    return 0;
}