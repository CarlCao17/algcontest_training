#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

void to_lower(string& s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
}

string repr(const string& s) {
    string ans = s;
    to_lower(ans);
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    string s;
    map<string, vector<int>> dict;
    vector<string> words;
    while (cin >> s) {
        if (s == "#") break;
        words.push_back(s);
        string r = repr(s);
        if (!dict.count(r)) dict[r] = vector<int>();
        dict[r].push_back(words.size()-1);
    }
    vector<string> ans;
    for (const auto& pair: dict) {
        if (pair.second.size() == 1) {
            ans.push_back(words[pair.second[0]]);
        }
    }
    sort(ans.begin(), ans.end());
    for (const string& word : ans) {
        cout << word << endl;
    }
}
