#include<cstdio>
#include<map>

struct Node {
    int idx;
    Node* prev;
    Node* next;
    Node(int idx): idx(idx), prev(nullptr), next(nullptr) {}
    Node(int idx, Node *prev, Node *next): idx(idx), prev(prev), next(next) {}
};

struct List {
    Node *head, *tail;
};
std::map<int, Node*> pos;

const int maxn = 100000+5;

void del_node(Node *target) {
    target->prev->next = target->next;
    target->next->prev = target->prev;
}

// y 插到 x 后面
// y != x
void insert_after(Node *x, Node *y) {
    y->next = x->next;
    y->next->prev = y;

    x->next = y;
    y->prev = x;
}

// y 插到 x 前面
// y != x
void insert_before(Node *x, Node *y) {
    Node *prev = x->prev;
    insert_after(prev, y);
}

void swap_node(Node *n1, Node *n2) {
    int n1_before_n2 = 0;
    for(Node *p = n1; p != nullptr; p = p->next) {
        if(p == n2) { n1_before_n2 = 1; break; }
    }
    if(n1_before_n2 == 0) n1_before_n2 = -1;

    Node *prev, *after;
    if(n1_before_n2 > 0) {
        prev = n1->prev;
        after = n2->next;
    }else {
        prev = n2->prev;
        after = n1->next;
    }

    del_node(n1);
    del_node(n2);
    if(n1_before_n2 > 0) {
        insert_after(prev, n2);
        insert_before(after, n1);
    } else {
        insert_after(prev, n1);
        insert_before(after, n2);
    }
}

// y 移动到 x 左边
// x != y
void move_to_left(Node *x, Node *y) {
    if(x->prev == y) return;
    del_node(y);
    insert_before(x, y);
}

// y 移动到 x 右边
// x != y
void move_to_right(Node *x, Node *y) {
    if(x->next == y) return;
    del_node(y);
    insert_after(x, y);
}

//void reverse(List l) {
//    Node *p1 = l.head->next, *p2 = l.tail->prev;
//    while(p1 != p2 && p1->next != p2) {
//        Node *next = p1->next, *prev = p2->prev;
//        swap_node(p1, p2);
//        p1 = next;
//        p2 = prev;
//    }
//    if(p1 != p2) {
//        swap_node(p1, p2);
//    }
//}

List build_list(int n) {
    Node* head = new Node(0); // head node
    Node* tail = new Node(n+1);
    head->next = tail;
    tail->prev = head;

    Node *prev = head;
    for(int i = 1; i <= n; i++) {
        Node *t = new Node(i);
        pos[i] = t;
        insert_after(prev, t);
        prev = t;
    }
    return List{.head = head, .tail = tail};
}

void print_list(List l) {
    printf("head(%d)", l.head->idx);
    for(Node *p = l.head->next; p != l.tail; p = p->next) {
        printf(" <-> %d", p->idx);
    }
    printf(" <-> tail(%d)\n", l.tail->idx);
}

int main() {
    int n, m;
    int cmd, x, y;
    int kase = 1;
    while(scanf("%d%d", &n, &m) == 2) {
        List list = build_list(n); // 注意要释放堆上分配的指针
        for(int i = 1; i <= m; i++) {
            scanf("%d", &cmd);
            if(cmd == 4) {
                reverse(list);
                continue;
            }
            scanf("%d%d", &x, &y);
            if(cmd == 1) {
                move_to_left(pos[y], pos[x]);
            } else if(cmd == 2) {
                move_to_right(pos[y], pos[x]);
            } else if(cmd == 3) {
                swap_node(pos[x], pos[y]);
            }
        }
        long long res = 0;
        int i = 1;
        for(Node *p = list.head->next; p != list.tail; p = p->next) {
            if(i) res += p->idx;
            i ^= 1;
        }
        printf("Case %d: %lld\n", kase++, res);
    }
}