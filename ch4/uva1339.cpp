#include<cstdio>
#include<cstring>
#include<cstdlib>

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

#define N 110
int main() {
    char s1[N], s2[N];
    int cnt1[26], cnt2[26];
    char *p;

    while(scanf("%s%s", s1, s2) == 2) {
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        for(p = s1; *p != '\0'; p++) cnt1[(*p)-'A']++;
        qsort(cnt1, 26, sizeof(int), cmp);
        for(p = s2; *p != '\0'; p++) cnt2[(*p)-'A']++;
        qsort(cnt2, 26, sizeof(int), cmp);

        bool res = true;
        for(int i = 0; i < 26; i++) {
            if(cnt1[i] != cnt2[i]) { res = false; break; }
        }
        if(res) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}