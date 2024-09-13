#include<cstdio>
#include<iostream>
#include<sstream>
#include<string>
#include<stack>
using namespace std;

int n;
struct Matrix {
    int r, c;
    explicit Matrix(int a = 0, int b = 0):r(a), c(b) {}
} m[26];

pair<Matrix, long> matrix_mul(Matrix A, Matrix B) {
    if(A.c != B.r) return pair<Matrix, long>(Matrix{}, -1);
    return pair<Matrix, long>(Matrix{.r =  A.r, .c =  B.c}, A.r * A.c * B.c);
}

long evaluate(string s) {
    long result = 0;
    stack<Matrix> st;
    for(auto ch : s) {
        if(ch == '(') continue;
        if(ch == ')') {
            if(st.empty()) return 0;
            Matrix B = st.top(); st.pop();
            if(st.empty()) return 0;
            Matrix A = st.top(); st.pop();
            pair<Matrix, long> p = matrix_mul(A, B);
            if(p.second == -1) return -1;
            result += p.second;
            st.push(p.first);
        } else {
            st.push(m[ch-'A']);
        }
    }
    return result;
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    ss >> n;

    while(n--) {
        getline(cin, line);
        stringstream ss(line);
        char ch;
        ss >> ch;
        ss >> m[ch-'A'].r >> m[ch-'A'].c;
    }

    long res = 0;
    while(std::getline(std::cin, line)) {
        res = evaluate(line);
        if(res == -1) printf("error\n");
        else printf("%ld\n", res);
    }
}