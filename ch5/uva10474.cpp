#include<cstdio>
#include<algorithm>
#define MAX_N 10001

int main() {
    int n, q;
    int nums[MAX_N];
    int x;
    int kase = 1;
    while (scanf("%d%d", &n, &q) == 2 && n ) {
        printf("CASE# %d:\n", kase++);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }
        std::sort(nums, nums+n);
        for (int i = 0; i < q; i++) {
            scanf("%d", &x);
            int idx = std::lower_bound(nums, nums+n, x) - nums;
            if (nums[idx] == x) {
                printf("%d found at %d\n", x, idx+1);
            } else {
                printf("%d not found\n", x);
            }
        }
    }
    return 0;
}
