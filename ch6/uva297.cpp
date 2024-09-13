#include<string>
#include<cstring>
//#include<math>
#include<iostream>
using namespace std;

struct Node {
    int val; // 0 - w, 1 - b, -1 - p
    int num;
    Node *child[4];

    Node() : val(-1) {
        child[0] = child[1] = child[2] = child[3] = NULL;
    }
    Node(int val) : val(val) {
        child[0] = child[1] = child[2] = child[3] = NULL;
    }
};

void build()


int main() {
    int kase;
    cin >> kase;
    while(kase--) {
        char ch; cin >> ch; // read \n
        build(p, 1);
        cin >> ch; // read \n
        build(q, 1);
        cout << "There are " << add(p, q) << " black pixels\n";
    }
}