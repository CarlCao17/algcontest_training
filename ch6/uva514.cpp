#include<cstdio>
#include<stack>
#include<vector>
using namespace std;

int n;

bool solve(vector<int>& B) {
    stack<int> s;
    int A = 1, j = 0;
    while(j < n) {
        if(A <= n && A == B[j]) ++A, ++j;
        else if(!s.empty() && s.top() == B[j]) s.pop(), ++j;
        else if(A <= n) s.push(A++);
        else return false;
    }
    return true;
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        vector<int> B(n);
        int num = 0;
        while(scanf("%d", &num) == 1 && num) {
            B[0] = num;
            int i = 1;
            while(i < n) scanf("%d", &B[i++]);
            if(solve(B)) printf("Yes\n");
            else printf("No\n");
        }
        printf("\n");
    }
}