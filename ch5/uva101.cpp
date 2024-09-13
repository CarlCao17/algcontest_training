#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int n;
const int maxn = 25;
vector<int> pile[maxn];

void find_block(int x, int& p, int& h) {
    for (p = 0; p < n; p++) {
        for (h = 0; h < pile[p].size(); h++) {
            if (pile[p][h] == x) {
                return;
            }
        }
    }
}

void clear_above(int p, int h) {
    for (int i = pile[p].size()-1; i >= h+1; i--) {
        int b = pile[p][i];
        pile[b].push_back(b);
    }
    pile[p].resize(h+1);
}

void pile_onto(int pa, int ha, int pb) {
    for (int i = ha; i < pile[pa].size(); i++) {
        int b = pile[pa][i];
        pile[pb].push_back(b);
    }
    pile[pa].resize(ha);
}

void print_ans() {
    for (int i = 0; i < n; i++) {
        cout << i << ":";
        for (int j = 0; j < pile[i].size(); j++) {
            cout << " " << pile[i][j];
        }
        cout <<endl;
    }
}

int main() {
    int a, b;
    string s1, s2;
    int pa, ha;
    int pb, hb;

    cin >> n;
    for (int i = 0; i < n; i++) {
        pile[i].push_back(i);
    }
    while(cin >> s1) {
        if (s1[0] == 'q') break;
        cin >> a >> s2 >> b;
        find_block(a, pa, ha);
        find_block(b, pb, hb);
        if (pa == pb) continue;
        if (s2 == "onto") clear_above(pb, hb);
        if (s1 == "move") clear_above(pa, ha);
        pile_onto(pa, ha, pb);
    }
    print_ans();
    return 0;
}