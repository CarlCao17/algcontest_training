#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 100;
int sum[maxn];

void build(int pos) {
    int num;
    cin >> num;
    if(num < 0) return;
    sum[pos] += num;
    build(pos-1);
    build(pos+1);
}

bool init() {
    int num;
    cin >> num;
    memset(sum, 0, sizeof(sum));
    if(num < 0) return false;

    int pos = maxn / 2;
    sum[pos] += num;
    build(pos-1);
    build(pos+1);
    return true;
}

int main() {
    int kase = 0;
    while(init()) {
        int p = 0;
        while(sum[p] == 0) p++;

        cout << "Case " << ++kase <<":\n" << sum[p++];
        while(sum[p]) {
            cout << " " << sum[p++];
        }
        cout << "\n\n";
    }
    return 0;
}