#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

// 这个版本使用静态数组 + 空闲列表实现一个简单的内存池

using namespace std;

const int maxn = 100000;
char s[maxn];
bool failed;

const int batch = 10240;

struct Node {
    bool have_value;
    int v;
    Node *l, *r;
    Node(): have_value(false), l(NULL), r(NULL) {}

    void recycle() {
        have_value = false; v = 0; l = r = NULL;
    }
} nodes[batch];

Node *root;
queue<Node*> freenodes;

void init() {
    for(int i = 0; i < maxn; i++) {
        freenodes.push(&nodes[i]);
    }
}

Node* newnode() {
    if(freenodes.empty()) {
        Node *p = new Node[batch]();
        for(int i = 0; i < batch; i++) {
            freenodes.push(p);
            p++;
        }
    }
    Node *p = freenodes.front(); freenodes.pop();
    p->recycle();
    return p;
}

void deletenode(Node *p) {
    freenodes.push(p);
}

void addnode(int v, char *path) {
    int n = strlen(path);
    Node *p = root;
    for(int i = 0; i < n; i++) {
        if(path[i] == 'L') {
            if(p->l == NULL) p->l = newnode();
            p = p->l;
        } else if(path[i] == 'R') {
            if(p->r == 0) p->r = newnode();
            p = p->r;
        }
    }
    if(p->have_value) failed = true;
    p->v = v;
    p->have_value = true;
}

void deletetree(Node *p) {
    if(p == NULL) return;
    deletetree(p->l);
    deletetree(p->r);
    deletenode(p);
}

bool read_input() {
    failed = false;
    deletetree(root);
    root = newnode();
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
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node *cur = q.front(); q.pop();
        if(!cur->have_value) return false;
        v.push_back(cur->v);
        if(cur->l) q.push(cur->l);
        if(cur->r) q.push(cur->r);
    }
    return true;
}

int main() {
    init();
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