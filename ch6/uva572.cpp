#include<cstdio>
#include<cstring>

const int maxn = 100 + 5;
char pic[maxn][maxn];
int idx[maxn][maxn];
int m, n;

void dfs(int i, int j, int id) {
//    if(!pic[i][j]) return;
    if(pic[i][j] != '@' || idx[i][j]) return; // invalid or '*' or has visited
    idx[i][j] = id;
    for(int r = -1; r <= 1; r++) {
        for(int c = -1; c <= 1; c++) {
            if(r != 0 && c != 0) dfs(i+r, j+c, id);
        }
    }
}

int main() {
    memset(pic, 0, sizeof(pic));

    while(scanf("%d%d", &m, &n) && m && n) {
        memset(idx, 0, sizeof(idx));
//        int ch = getchar(); // read the newline
        for(int i = 1; i <= m; i++) {
            scanf("%s", &pic[i][1]);
        }
        int cnt = 0;
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(pic[i][j] == '@' && !idx[i][j]) dfs(i, j, ++cnt);
            }
        }
        printf("%d\n", cnt);
    }
}