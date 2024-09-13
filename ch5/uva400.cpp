//#include "bits/stdc++.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

void print_word(const string& s, int len, char extra) {
    cout << s;
    for(int i = s.length(); i < len; i++) cout << extra;
}

const int maxcol = 60;
const int maxn = 100+5;
string filenames[maxn];

int main() {
     std::ios::sync_with_stdio(false);
     std::cin.tie(nullptr);

    int n;
    int rows, cols;

    while(cin >> n) {
        int M = 0;
        for(int i = 0; i < n; i++) {
            cin >> filenames[i];
            M = max(M, (int)filenames[i].length());
        }
        cols = (maxcol - M)/(M+2)+1;
        rows = (n-1)/cols + 1;

        print_word("", maxcol, '-');
        cout << endl;
        sort(filenames, filenames+n);
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                int idx = c * rows + r;
                if (idx < n) {
                    print_word(filenames[idx], c == cols-1 ? M : M+2, ' ');
                }
            }
            cout << endl;
        }
    }
    return 0;
}