//
// Created by 曹正盛 on 24-8-11.
//
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 100+10;
int A[maxn];
int main() {
    long long a, b;
    while (cin >> a >> b) {
        cout << min(a,b) << "\n";
    }
    return 0;
}