#include<cstdio>
#include<limits>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

const int maxn = 10000+5;
//int t[maxn];
vector<int> inorder;
vector<int> postorder;
int min_value;
int res;

// 递归爆栈
void build_and_traverse(int l, int r, int lp, int root_pos, int sum) {
    if(l >= r) return;
    int root = postorder[lp+(r-l)-1];
//    t[root_pos] = root;
    sum += root;

    if(l == r-1) {
        if(sum <= min_value) {
            min_value = sum; res = root;
        }
        return;
    }
    auto it = find(inorder.begin()+l, inorder.begin()+r, root);
    int idx = distance(inorder.begin(), it);
    build_and_traverse(l, idx, lp, 2*root_pos, sum);
    build_and_traverse(idx+1, r, lp+(idx-l),2*root_pos+1, sum);
}

struct Pos {
    int l, r, lp, sum;
};

// 利用 inorder 和 postorder 来重构 BFS 序列
void build_and_traverse2(Pos pos) {
    stack<Pos> s;
    s.push(pos);

    while(!s.empty()) {
        auto p = s.top(); s.pop();
        if(p.l >= p.r) continue;
        int rp = p.lp + p.r - p.l -1;
        int root = postorder[rp];
        int sum = p.sum + root;

        if(p.l == p.r-1) {
            if(sum <= min_value) {
                min_value = sum; res = root;
            }
            continue;
        }
        int idx = distance(inorder.begin(), find(inorder.begin()+p.l, inorder.begin()+p.r, root));
        Pos l = Pos{l: p.l, r: idx, lp: p.lp, sum: sum};
        s.push(l);
        Pos r = Pos{l: idx+1, r: p.r, lp: p.lp+(idx-p.l), sum: sum};
        s.push(r);
    }
}

void parse(string& line1, string& line2) {
    int n;
    stringstream ss(line1);
    while(ss >> n) {
        inorder.push_back(n);
    }
    ss = stringstream(line2);
    while(ss >> n) {
        postorder.push_back(n);
    }
}

int main() {
    string line1, line2;
    while(getline(std::cin, line1) && getline(std::cin, line2)) {
        vector<int> empty;
        inorder.swap(empty);
        vector<int> empty2;
        postorder.swap(empty2);
        parse(line1, line2);

        int n = inorder.size();

        min_value = numeric_limits<int>::max();
        build_and_traverse2(Pos{l: 0, r: n, lp: 0, sum: 0});
        printf("%d\n", res);
//        print_tree(n);
    }
}