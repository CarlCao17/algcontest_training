#include<random>
#include<chrono>
#include<iostream>
#include<queue>
#include<set>
#include<vector>
using namespace std;

#define N 1500

typedef long long LL;

int main() {
    std::ios::sync_with_stdio(false);

    priority_queue<LL, std::vector<LL>, std::greater<LL> > pq;
    set<LL> vis;
    pq.push(1);
    vis.insert(1);

    LL nums[3] = {2,3,5};
    for (int i = 1; ; i++) {
        LL x = pq.top(); pq.pop();
        if (i == N) {
            cout << "The 1500'th ugly number is " << x << ".\n";
            break;
        }
        for (int j = 0; j < 3; j++) {
            LL x2 = x * nums[j];
            if (!vis.count(x2)) {
                vis.insert(x2); pq.push(x2);
            }
        }
    }
    return 0;
}