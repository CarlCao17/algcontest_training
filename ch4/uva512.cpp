#include<cstdio>
#include<cstring>
#include<algorithm>

#define maxrows  1000
#define maxcols  1000
#define DELETED -1
#define INSERT 0
#define VALUE(r,c) (r)*maxcols+(c)

struct Command {
    char cmd[20];
    int r1, c1, r2, c2;
    int a;
    int x[20];
};

int r, c, n;

int nr,nc;
int org_r, org_c;
int rev_row_views[maxrows];
int rev_col_views[maxcols];

int data[maxrows][maxcols];

void exchange(int r1, int c1, int r2, int c2) {
    int new_r1 = rev_row_views[r1], new_c1 = rev_col_views[c1];
    int new_r2 = rev_row_views[r2], new_c2 = rev_col_views[c2];
    int t = data[new_r1][new_c1];
    data[new_r1][new_c1] = data[new_r2][new_c2];
    data[new_r2][new_c2] = t;
}

void del(char type, int k) {
    if(type == 'R') {
        for(int j = 1; j <= org_c; j++) {
            data[k][j] *= DELETED;
        }
    } else {
        for(int i = 1; i <= org_r; i++) {
            data[i][k] *= DELETED;
        }
    }
}

void op(char op, char type, int x[], int a) {
    if(op == 'D') {
        if(type == 'R') {
            for(int i = a-1; i >= 0; i--) {
                int row_to_del = x[i];
                int org_row = rev_row_views[row_to_del];
                del(type, org_row);
                std::copy(rev_row_views+row_to_del+1, rev_row_views+nr+1, rev_row_views+row_to_del);
                nr--;
            }
        } else {
            for(int j = a-1; j >= 0; j--) {
                int col_to_del = x[j];
                int org_col = rev_col_views[col_to_del];
                del(type, org_col);
                std::copy(rev_col_views+col_to_del+1, rev_col_views+nc+1, rev_col_views+col_to_del);
                nc--;
            }
        }
    } else {
        if(type == 'R') {
            for(int i = a-1; i >= 0; i--) {
                int row_to_ins = x[i];
                std::copy(rev_row_views+row_to_ins, rev_row_views+nr+1, rev_row_views+row_to_ins+1);
                ++nr; ++org_r;
                rev_row_views[row_to_ins] = org_r; // 默认新增的 data 行或者列已经 初始化未了 INSERT
            }
        } else {
            for(int j = a-1; j >= 0; j--) {
                int col_to_ins = x[j];
                std::copy(rev_col_views+col_to_ins, rev_col_views+nc+1, rev_col_views+col_to_ins+1);
                ++nc; ++org_c;
                rev_col_views[col_to_ins] = org_c;
            }
        }
    }
}

void query(int r, int c) {
    printf("Cell data in (%d,%d) ", r, c);
    int val = VALUE(r,c);
    int posi = -1, posj = -1;
    for(int i = 1; i <= org_r; i++) {
        for(int j = 1; j <= org_c; j++) {
            if(data[i][j] == val || data[i][j] == DELETED*val) { // 找到原来的 VALUE(r,c) 最后的位置，可能位置被删除
                posi = i;
                posj = j;
                break;
            }
        }
    }
    int rev_r = -1, rev_c = -1;
    for(int i = 1; i <= nr; i++) {
        if(rev_row_views[i] == posi) {
            rev_r = i; break;
        }
    }
    for(int j = 1; j <= nc; j++) {
        if(rev_col_views[j] == posj) {
            rev_c = j; break;
        }
    }
    if(rev_r == -1 || rev_c == -1) {
        printf("GONE\n"); return;
    }
    printf("moved to (%d,%d)\n", rev_r, rev_c);
}

int main() {
    int kcase = 0;
    while(scanf("%d%d", &r, &c) == 2 && r) {
        memset(data, INSERT, sizeof(data));
        nr = r, nc = c;
        org_r = r, org_c = c;
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                data[i][j] = VALUE(i,j);
            }
        }
        for(int i = 1; i <= nr; i++) rev_row_views[i] = i;
        for(int i = 1; i <= nc; i++) rev_col_views[i] = i;

        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            Command cmd;
            scanf("%s", &cmd.cmd);
            if(cmd.cmd[0] == 'E') {
                scanf("%d%d%d%d", &cmd.r1, &cmd.c1, &cmd.r2, &cmd.c2);
                exchange(cmd.r1, cmd.c1, cmd.r2, cmd.c2);
            } else {
                scanf("%d", &cmd.a);
                for(int i = 0; i < cmd.a; i++) {
                    scanf("%d", &cmd.x[i]);
                }
                std::sort(cmd.x, cmd.x+cmd.a);
                op(cmd.cmd[0], cmd.cmd[1], cmd.x, cmd.a);
            }
        }

        int nq;
        scanf("%d", &nq);
        if(kcase > 0) printf("\n");
        printf("Spreadsheet #%d\n", ++kcase);
        for(int i = 0; i < nq; i++) {
            int r, c;
            scanf("%d%d", &r, &c);
            query(r, c);
        }
    }
    return 0;
}