#include<cstdio>
#include <cstring>

const int maxn = 100000+100;
char line[maxn];
int next[maxn];
int last, curr;
int lastFlag = -1;

int main() {
    while(scanf("%s", line+1) == 1) {
        int n = strlen(line+1);
        last = curr = 0;
        next[0] = lastFlag;

        for(int i = 1; i <= n; i++) {
            if(line[i] == '[') curr = 0;
            else if(line[i] == ']') curr = last;
            else {
                next[i] = next[curr];
                next[curr] = i;
                if(curr == last) last = i; // 更新最后一个字符编号
                curr = i; // 移动光标
            }
        }

        for(int i = next[0]; i != lastFlag; i = next[i])
            printf("%c", line[i]);
        printf("\n");
    }
    return 0;
}