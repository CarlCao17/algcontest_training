//
// Created by 曹正盛 on 24-8-11.
//
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<cstdio>
#include"../utility.h"
using namespace std;

void mock_test(string file_name, int n) {
    ofstream file(file_name);
    if (!file.is_open()) {
        cerr << "can not open the file "<< "\n";
        return ;
    }
    for (int i = 0; i < n; i++) {
        int cnt = get_random_number(1000000);
        vector<int> vec(cnt);
        fill_random_int(vec, 0, 1000000000);
        for(const auto& num : vec) {
            file << num << " ";
        }
        cout << "case " << i << " write " << cnt << " numbers into file"<<endl;
    }

    file.close();
}



int main() {
//    mock_test("in.txt", 1000);
//    string line;
//    while(getline(cin, line)) {
//        int sum = 0, x;
//        stringstream ss(line);
//        while(ss >> x) sum += x;
//        cout << sum << "\n";
//    }
//    return 0;

}