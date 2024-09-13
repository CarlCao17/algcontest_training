#include<cstdio>
#include<iostream>
#include<sstream>
#include<stack>
//#include<queue>
#include<string>
using namespace std;

struct Node {
    int sum;
    int wl, wr;
    int dl, dr;
    Node *l, *r;

    Node(int wl, int dl, int wr, int dr) : sum(0), wl(wl), wr(wr), dl(dl), dr(dr), l(NULL), r(NULL) {};
};

bool solve(Node* p) {
    if(p == NULL) return true;
    if(!solve(p->l)) return false;
    if(!solve(p->r)) return false;
    return (p->wl*p->dl) == (p->wr *p->dr);
}

Node* parse(string& s) {
    stringstream ss(s);
    int wl, dl, wr, dr;
    ss >> wl >> dl >> wr >> dr;
    Node *p = new Node(wl, dl, wr, dr);
    return p;
}

Node* build() {
    string line;
    if(!getline(std::cin, line) || line.empty()) return NULL;
    Node *root = parse(line);
    if(root->wl == 0) {
        root->l = build();
        root->wl = root->l->sum;
    }if(root->wr == 0) {
        root->r = build();
        root->wr = root->r->sum;
    }
    root->sum = root->wl + root->wr;
    return root;
}

//void print_tree(Node *p) {
//    queue<Node*> q;
//    if(p == NULL) return;
//    q.push(p);
//    while(!q.empty()) {
//        Node* c = q.front(); q.pop();
//        printf("[sum=%d, wl=%d, wr=%d, dl=%d, dr=%d]", c->sum, c->wl, c->wr, c->dl, c->dr);
//        if(c->l) q.push(c->l);
//        if(c->r) q.push(c->r);
//    }
//}

int main() {
    string line;
    int kase;
    getline(std::cin, line);
    stringstream ss(line);
    ss >> kase;
    while(kase--) {
        getline(std::cin, line);

        Node *root = build();
//        print_tree(root);
        if(solve(root)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        if(kase > 0) printf("\n");
    }
}