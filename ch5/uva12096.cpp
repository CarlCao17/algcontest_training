#include<iostream>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

#define All(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

typedef set<int> Set;
map<Set, int> IDCache;
vector<Set> SetCache;

int ID(Set x) {
    if (IDCache.count(x)) return IDCache[x];
    SetCache.push_back(x);
    IDCache[x] = SetCache.size()-1;
    return SetCache.size()-1;
}

int main() {
    int t, n;

    cin >> t;
    for (int i = 0; i < t; i++) {
        string cmd;
        stack<int> Stack;

        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> cmd;
            if (cmd == "PUSH") Stack.push(ID(Set()));
            else if (cmd == "DUP") Stack.push(Stack.top());
            else {
                Set x1 = SetCache[Stack.top()]; Stack.pop();
                Set x2 = SetCache[Stack.top()]; Stack.pop();
                Set x;
                if (cmd == "UNION") {
                    set_union(All(x1), All(x2), INS(x));
                } else if (cmd == "INTERSECT") {
                    set_intersection(All(x1), All(x2), INS(x));
                } else if (cmd == "ADD") {
                    x = x2;
                    x.insert(ID(x1));
                }
                Stack.push(ID(x));
            }
            cout << SetCache[Stack.top()].size() << endl;
        }
        cout << "***" << endl;
    }
}