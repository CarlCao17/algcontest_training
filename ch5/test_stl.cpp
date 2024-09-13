#include"../bits/stdc++.h"
#include"../utility.h"
#include<cassert>

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;

typedef pair<long long, long long> PLL;
const int mod = 998244353;
const int N = static_cast<const int>(2e6+1000);
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-6;
mt19937_64 rnd(static_cast<unsigned long long int>(chrono::steady_clock::now().time_since_epoch().count()));

void test_sort(vector<int>& v) {
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size()-1; i++) {
        assert(v[i] <= v[i+1]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);
    vector<int> v(N);
    fill_random_int(v, N);
    test_sort(v);
    return 0;
}