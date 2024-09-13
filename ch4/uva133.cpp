#include<cstdio>
#define N 20+1

int nums[N];
int n;

// 逆时针走 t 步，步长为 step，如果 step < 0 表示顺时针走，返回新位置
int go_step(int curr, int step, int t) {
     while(t--) {
         do { curr = (curr+step+n-1) % n + 1; } while(nums[curr] == -1);
     }
     return curr;
}

int main() {
    int k, m;
    while(scanf("%d%d%d", &n, &k, &m) == 3 && n) {
        for(int i = 1; i <= n; i++) nums[i] = i;

        int left = n;
        int a = 0, b = n+1;
        while(left) {
            a = go_step(a, 1, k);
            b = go_step(b, -1, m);
            if(left < n) {
                printf(",");
            }
            printf("%3d", nums[a]);
            nums[a] = -1;
            left--;
            if(a != b) {
                printf("%3d", nums[b]);
                nums[b] = -1;
                left--;
            }
        }
        printf("\n");
    }
    return 0;
}