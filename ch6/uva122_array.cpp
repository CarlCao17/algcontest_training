#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int maxn = 100000;
char s[maxn];
const int root = 1;
int cnt;
int val[maxn];
int left[maxn], right[maxn];
bool have_value[maxn];
bool failed;

void newtree() {
    left[root] = right[root] = 0; have_value[root] = false; cnt = root;
}

int newnode() {
    int u = ++cnt;
    left[u] = right[u] = 0;
    have_value[u] = false;
    return u;
}

void addnode(int v, char *path) {
    int n = strlen(path);
    int p = root;
    for(int i = 0; i < n; i++) {
        if(path[i] == 'L') {
            if(left[p] == 0) left[p] = newnode();
            p = left[p];
        } else if(path[i] == 'R') {
            if(right[p] == 0) right[p] = newnode();
            p = right[p];
        }
    }
    if(have_value[p]) failed = true;
    val[p] = v;
    have_value[p] = true;
}

bool read_input() {
    failed = false;
    newtree();
    while(true) {
        if(scanf("%s", s) != 1) return false;
        if(!strcmp(s, "()")) break;
        int v;
        sscanf(s+1, "%d", &v);
        addnode(v, strchr(s, ',')+1);
    }
    return true;
}

bool bfs(vector<int>& v) {
    queue<int> q;
    q.push(root);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        if(!have_value[cur]) return false;
        v.push_back(val[cur]);
        if(left[cur]) q.push(left[cur]);
        if(right[cur]) q.push(right[cur]);
    }
    return true;
}

int main() {
    while(read_input()) {
        if(failed) { printf("not complete\n"); continue; }
        vector<int> v;
        if(!bfs(v)) { printf("not complete\n"); continue; }
        for(int i = 0; i < v.size(); i++) {
            if(i > 0) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    }
}