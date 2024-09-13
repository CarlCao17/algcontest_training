#include<cstdio>
#include <cstring>
#include<vector>
#include<queue>

using namespace std;

struct Node {
    bool have_value;
    int v;
    Node *l, *r;
    Node(): have_value(false), l(nullptr), r(nullptr) {}
};

const int maxn = 100000;
char s[maxn];
Node *root;
bool failed;

Node* newnode() {
    return new Node();
}

void addnode(int v, char *path) {
    int n = strlen(path);
    Node *p = root;
    for(int i = 0; i < n; i++) {
        if(path[i] == 'L') {
            if(p->l == nullptr) p->l = newnode();
            p = p->l;
        } else if(path[i] == 'R') {
            if(p->r == nullptr) p->r = newnode();
            p = p->r;
        }
    }
    if(p->have_value) failed = true;
    p->v = v;
    p->have_value = true;
}

void delete_tree(Node *p) {
    if(p == nullptr) return;
    delete_tree(p->l);
    delete_tree(p->r);
    delete p;
}

bool read_input() {
    failed = false;
    delete_tree(root);
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