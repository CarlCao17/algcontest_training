#include"bits/stdc++.h"
#include<cstdio>

#define N 100+1

typedef struct Rec {
    int a, b;
} Rec;

int readLines(Rec rec[]) {
    int n;
    scanf("%d", &n);
   
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &rec[i].a, &rec[i].b);
    }
    return n;
}

int canBeNested(Rec& src, Rec& dst) {
    return (src.a < dst.a && src.b < dst.b) || (src.b < dst.a && src.a < dst.b);
}

// G[i][j] 表示从 i 到 j 存在一条边，也就是 rec[i] 可以嵌套进 rec[j]
void buildGraph(Rec rec[N], int G[N][N], int n) {
    std::memset(G, -1, N*N*sizeof(int));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            G[i][j] = canBeNested(rec[i], rec[j]);
        }
    }
}

// dp(i) = 以 i 为起点的最长路径
int dp(int G[N][N], int i, int d[N], int next[N], int n) {
    if (next[i]) return d[i];
    int& ans = d[i];
    int next_idx = i;
    for (int j = 1; j <= n; j++) {
        if (G[i][j]) {
            int curr = dp(G, j, d, next, n) + 1;
            if (curr > ans) {
                ans = curr;
                next_idx = j;
            }
        };
    }
    next[i] = next_idx;
    return ans;
}

void print_ans(Rec rec[N], int next[N], int start) {
    int i = start;
    while (next[i] != i) {
        std::cout << "rectangle(" << i << rec[i].a << rec[i].b << ") -> ";
        i = next[i];
    }
    std::cout << "rectangle(" << i << rec[i].a << rec[i].b << ")";
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Rec rec[N];
    int next[N];
    int G[N][N];
    int d[N];
    int n = readLines(rec);
    buildGraph(rec, G, n);
    memset(next, 0, N*sizeof(int));
    memset(d, 0, N*sizeof(int));
    // std::cout<< "graph:"<<'\n';
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         std::cout<< G[i][j] << " ";
    //     }
    //     std::cout<<'\n';
    // }
    int start = 0;
    int max = 0;
    for (int i = 1; i <= n; i++) {
        int t = dp(G, i, d, next, n);
        if (t > max) {
            max = t;
            start = i;
        }
    }
    std::cout << "the longest path:\n";
    print_ans(rec, next, start);
    std::cout << "path len = " << max << "\n";
    return 0;
}